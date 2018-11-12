from __future__ import print_function
import sys
import os
import csv

def parse_homeowners(csv_file):
    with open(csv_file, 'r') as f:
        reader = csv.DictReader(f, delimiter="\t")
        return [x for x in reader]

if __name__ == "__main__":
    parse_homeowners(sys.argv[1])
