from sys import argv, exit
import csv
from collections import defaultdict

if len(argv) != 3:
    print("missing command-line argument")
    exit(1)

## key in dictionary is name of person
## value is array where indecies mean 0 - AGATC, 1 - AATG, 2 - TATC
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
                for s in row:
                    if s != "name":
                        rst.append(s)
            else:
                n = 0
                for r in row:
                    if n != 0:
                        base[row[0]].append(int(r))
                    n += 1
    return rst                

def longest_chain(dna, str):
    chain = 0
    temp = 0
    seq = False
    i = 0
    while i < len(dna):
        n = 0
        while n < len(str) and n + i < len(dna):
            if dna[i + n] == str[n]:
                bl = True
                n += 1
            else:
                bl = False
                break
        if bl:
            temp += 1
            seq = True
            i += len(str)
        elif seq:
            seq = False
            i += 1
            chain = temp if temp > chain else chain
            temp = 0
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
        i = 0
        tmp = False
        for el in counts:
            if el == value[i]:
                tmp = True
                i += 1
            else:
                tmp = False
                break
        if tmp:
            print(name)
            break
    if tmp == False:
         print("No match")

__main__()