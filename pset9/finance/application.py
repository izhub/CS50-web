import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set |   export API_KEY=pk_3247946c04664522b2983f9aa6ea5599&&flask run
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    name = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if request.method == "POST":

        if not name or not password or not confirmation:
            return apology("fields cannot be blank", 400)

        elif name:
            rows = db.execute("SELECT * FROM users WHERE username = ?", name)
            if len(rows) == 1:
                return apology("username already exists", 400)

            elif password and confirmation:
                if password != confirmation:
                    return apology("password did not match", 400)

                else:
                    db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, generate_password_hash(password))
                    return redirect("/")
    else:
        return render_template("register.html")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    info = db.execute("SELECT users.cash, buy.symbol, buy.shares FROM buy JOIN users ON users.id = buy.user_id WHERE buy.user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = 0.0
    for i in info:
        c = lookup(i["symbol"])
        i["price"] = c["price"]
        i["name"] = c["name"]
        i["total"] = float(i["price"]) * int(i["shares"])
        total += i["total"]

    return render_template("index.html", info=info, cash=cash, total=cash + total)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote.""" """ NFLX """

    if request.method == "POST":
        s = request.form.get("symbol")
        company = lookup(s)

        if not s:
            return apology("fields can't be blank", 400)

        elif not s.isalpha():
            return apology("Can't be a number", 400)

        elif lookup(s) == None:
            return apology("Invalid symbol", 400)

        else:
            return render_template("quoted.html", quote=company)

    else:
        return render_template("quote.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        company = lookup(symbol)
        shares = request.form.get("shares")
        # ensure proper symbol
        if not symbol or company == None:
            return apology("Invalid symbol", 400)

        if shares.isnumeric() == False:
            return apology("Invalid number", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        stock = int(shares) * float(company["price"])

        if not cash or cash < stock:
            return apology("Insufficient Funds", 400)

        # update cash
        db.execute('UPDATE users SET "cash" = ? WHERE "id" = ?', cash - stock, session["user_id"])

        # add to history
        db.execute("INSERT INTO history (user_id, symbol, status, shares, price,transacted) VALUES (?, ?, 'B', ?, ?, datetime('now'))",
                session["user_id"], company["symbol"],  int(shares), company["price"])

        user_shares = db.execute("SELECT shares FROM buy WHERE symbol = ? and user_id = ?", symbol, session["user_id"])

        if not user_shares:
            db.execute("INSERT INTO buy (user_id, symbol, shares, price,transacted) VALUES (?, ?, ?, ?, datetime('now'))",
                session["user_id"], company["symbol"], int(shares), company["price"])

        else:
            ts = int(shares) + user_shares[0]["shares"]
            db.execute('UPDATE buy SET "shares" = ? WHERE "user_id" = ? AND "symbol" = ? ', ts, session["user_id"], i['symbol'])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")
    info = db.execute("SELECT DISTINCT buy.symbol, buy.shares, users.cash FROM buy JOIN users ON users.id = buy.user_id WHERE buy.user_id = ?", session["user_id"])
    cash = info[0]["cash"]
    share = 0

    if symbol != None:
        company = lookup(symbol)

    for i in info:
        if i["symbol"] == symbol:
            share = i["shares"]

    if request.method == "POST":

        if not shares or not symbol:
            return apology("fields cannot be blank", 400)

        elif symbol:
            if symbol not in [d['symbol'] for d in info]:
                return apology("not found", 400)

            elif share < int(shares):
                return apology("Insufficient shares", 400)

            else:
                db.execute("INSERT INTO history (user_id, symbol, status, shares, price, transacted) VALUES (?, ?, 'S', ?, ?, datetime('now'))",
                    session["user_id"], company["symbol"],  -int(shares), company["price"])

                db.execute('UPDATE users SET "cash" = ? WHERE "id" = ?',
                    cash + (int(shares) * company["price"]), session["user_id"])

                db.execute('UPDATE buy SET "shares" = ? WHERE "user_id" = ? AND "symbol" = ? ',
                    share - int(shares), session["user_id"], company['symbol'])

            return redirect("/")
    else:
        return render_template("sell.html", info=info)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    info = db.execute("SELECT symbol, status, shares,price, transacted FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", info=info)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
