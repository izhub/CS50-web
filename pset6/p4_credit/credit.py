from cs50 import get_int


def main():

    n = get_int("Enter Number: ")
    n2 = n
    rem = 0
    count = 0
    checksum = 0

    while n != 0:
        rem = n % 10
        n //= 10
        count += 1

    n = n2
    n //= 10
    while n != 0:
        s = (n % 10) * 2
        if s > 9:
            r = s % 10
            s = s // 10
            r2 = s % 10
            checksum += r + r2
        else:
            checksum += s
        n //= 100

    n = n2
    while n != 0:
        checksum += n % 10
        n //= 100

    fdigit = n2 // pow(10, count - 1)
    fdigit2 = n2 // pow(10, count - 2)
    ldigit = checksum % 10

    if ldigit == 0 and count == 13 or count == 16 and fdigit == 4:
        print("VISA")
    elif ldigit == 0 and count == 15 and fdigit2 == 34 or fdigit2 == 37:
        print("AMEX")
    elif ldigit == 0 and count == 16 and (fdigit2 > 50 or fdigit2 < 56):
        print("MASTERCARD")
    elif ldigit != 0 and count != 15 or count != 16 or count != 13:
        print("INVALID")


main()

# style50 credit.py
# check50 cs50/problems/2021/x/sentimental/credit
# submit50 cs50/problems/2021/x/sentimental/credit