-- run 'sqlite3 movies.db' so that you can begin executing queries on the database.

-- write a SQL query to list the titles of all movies released in 2008.

SELECT title FROM movies WHERE year = 2008;


-- To test your queries on CS50 IDE, you can query the database by running
-- $ cat filename.sql | sqlite3 movies.db
-- where filename.sql is the file containing your SQL query.

-- You can also run
-- $ cat filename.sql | sqlite3 movies.db > output.txt
-- to redirect the output of the query to a text file called output.txt.
-- (This can be useful for checking how many rows are returned by your query!)


-- check50 cs50/problems/2021/x/movies
-- submit50 cs50/problems/2021/x/movies