def main():

    txt = input("Text: ")
    letters = 0
    words = len(txt.split())
    sentences = 0

    for c in txt:
        if c.isalpha():
            letters += 1
        elif c == '.' or c == '?' or c == '!':
            sentences += 1

    index = 0.0588 * avg(letters, words) - 0.296 * avg(sentences, words) - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade", round(index))


def avg(n, n2):
    return n / n2 * 100


main()

# style50 readability.py
# check50 cs50/problems/2021/x/sentimental/readability
# submit50 cs50/problems/2021/x/sentimental/readability