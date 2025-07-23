from cs50 import get_float


def main():

    while True:
        n = get_float("Change owed: ")
        if n > 0:
            break

    n = round(n * 100)
    tc = 0

    while n > 0:
        if n >= 25:
            n -= 25
            tc += 1

        elif n >= 10:
            n -= 10
            tc += 1

        elif n >= 5:
            n -= 5
            tc += 1

        else:
            n -= 1
            tc += 1

    print("Total Coins", tc)


main()

# check50 cs50/problems/2021/x/sentimental/cash
# submit50 cs50/problems/2021/x/sentimental/cash