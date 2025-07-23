from cs50 import get_int

def main():

    while True:
        n = get_int("height: ")
        if n > 0 and n < 9:
            break
    for i in range(n):
        print(" " * (n - 1 - i), end = "")
        for j in range(i + 1):
            print("#", end = "")
        print("  ", end = "")
        for k in range(i + 1):
            print("#", end = "")
        print()


main()

# check50 cs50/problems/2021/x/sentimental/mario/more
# submit50 cs50/problems/2020/x/sentimental/mario/more