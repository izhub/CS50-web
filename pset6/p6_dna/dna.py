# Implement a program that identifies a person based on their DNA
import collections
from sys import argv, exit
import csv
import re

# Ensure correct usage
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open dna file into to memory
with open(argv[2]) as txtfile:
    dna = txtfile.read()

# open database csv file  into memory
with open(argv[1]) as csvfile:
    cs = csv.reader(csvfile)
    header = next(cs)
    # store header row minus first column
    keys = header[1:]
    clist = []
    dnalist = []
    match = ""

    # number of consequtive STR repeats
    for k in keys:
        res = max(re.findall('((?:' + re.escape(k) + ')*)', dna), key=len)
        dnalist.append(res.count(k))

    # add db rows to list
    for row in cs:
        clist.append(row)

    # convert db string to int and compare list to dna list to find match
    for c in clist:
        # get name of person
        name = c[0]
        # get evertying from index 1 and beyond
        c = c[1:]
        c = [int(i) for i in c]
        if dnalist == c:
            match = name

    print(match) if match else print("No match")


# ---------------------------------------------------------
# consequtive STR repeats source:
# https://www.quora.com/How-do-I-get-the-number-of-consecutive-occurrences-of-a-substring-in-a-string-using-Python
# https://stackoverflow.com/questions/61131768/how-to-count-consecutive-substring-in-a-string-in-python-3

###########################

# open CSV file and DNA seq, read contents in memory
# For each STR, compute longest run consequctive repeat DNA Seq
# Compare STR counts against each row in CSV file, if match print name else no match

# Hints:
# Python's csv module has reader and DictReader
# Python's sys module gives access to sys.argv for command-line arguments
# Once open file f via open(filename), can read contents using f.read

# ----------------------
# Computer STR counts:
# for each position in seq: compute how many times repeat, start at that position
    # check successive substrings untl str repeats no longer, max num it repeats
# Hints: len(s) and s[i:j]

# def findmax(string, substr)
    # for i in range(len(string)):
    #     subcount = maxcount = 0
    #     j = i

    #     while string[j:j + len(substr)] == substr:
    #         subcount += 1
    #         j = j + len(substr)

    #     if subcount > maxcount:
    #         maxcount = subcount

    #     return maxcount

# -----------------------
# comparing against data:
# save STR counts in some data structe ( list?)
# for each row in data, check if each STR count matches, if so print name
# Hints:
    # int(x) take string x and turns into integer
    # to confirm match, check every column other than the first column

# with open(argv[1]) as csvfile:
#     cs = csv.reader(csvfile)
#     dblist = next(cs)[1:]

# with open(argv[2]) as txtfile:
#     dna = txtfile.read()
#     strcount = [findmax(dna, substr) for substr in dblist]

# ------------------------------------
# style50 dna.py
# check50 cs50/problems/2020/x/dna
# submit50 cs50/problems/2021/x/dna