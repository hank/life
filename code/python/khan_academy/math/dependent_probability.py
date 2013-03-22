#!/usr/bin/env python
desc = "Calculates the dependent probability"
import argparse
import khan_stat

parser = argparse.ArgumentParser(description=desc)
parser.add_argument('numbers', metavar="N", type=int, nargs="+")
args = parser.parse_args()
(coins, unfair, chance, flips) = args.numbers

probs = []
probs.append(((float(chance)/100.)**flips)*unfair/coins)
probs.append(((.5)**flips)*(coins-unfair)/coins)
print round(sum(probs)*100, 2), "%"
