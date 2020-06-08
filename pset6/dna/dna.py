from sys import argv, exit
import csv
from collections import defaultdict

if len(argv) != 3:
    print("missing command-line argument")
    exit(1)

# key in dictionary is name of person
# value is array of STRs
base = defaultdict(list)


def __main__():
    rst = dna_csv_reader()
    counters = dna_sequence_analizer(rst)
    check_matches(counters)


def dna_csv_reader():
    rst = []
    with open(argv[1]) as file:
        reader = csv.reader(file, delimiter=',')
        m = 0
        for row in reader:
            if m == 0:
                m += 1
                rst.extend(row[1:])
            else:
                for i in range(1, len(row)):
                    row[i] = int(row[i])
                base[row[0]] = row[1:]
    return rst


def longest_chain(dna, str):
    chain = 0
    temp = 0
    seq = False
    i = 0
    n = len(str)
    while i < len(dna):
        if dna[i:i+n] == str:
            seq = True
            temp += 1
            i += n
        elif seq:
            seq = False
            chain = temp if temp > chain else chain
            temp = 0
            i += 1
        else:
            i += 1
    return chain


def dna_sequence_analizer(rst):
    with open(argv[2]) as file:
        reader = file.readline()
    result = []
    for el in rst:
        result.append(longest_chain(reader, el))
    return result


def check_matches(counts):
    for name, value in base.items():
        if value == counts:
            print(name)
            exit()
    print("No match")


__main__()
