import binascii, argparse, struct, sys, math
from collections import Counter

def int2bin(n, count):
    """returns the binary of integer n, using count number of digits"""
    return "".join([str((n >> y) & 1) for y in range(count-1, -1, -1)])

def entropy(s):
    p, lns = Counter(s), float(len(s))
    return -sum( count/lns * math.log(count/lns, 2) for count in p.values())

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("sides")
    args = parser.parse_args()
    print "Using a die with {} sides".format(args.sides)
    # Find power of 2
    g = int(args.sides)
    h = 0
    while g > 1:
        g = int(g / 2)
        h += 1
    h = int(h)
    cutoff = 2**h
    print "{} is the cutoff, re-roll larger values".format(cutoff)
    rolls = ""
    rolls_required = 256/h
    print "Input {} dice rolls:".format(rolls_required)
    while rolls_required > 0:
        try:
            i = raw_input("Roll ({} left): ".format(rolls_required))
            i = int(i)
            if i > cutoff:
                print "Fail - you need to throw away values larger than {}".format(cutoff)
                continue
            elif i == 0:
                print "0 is not a valid dice roll!"
                continue
            print "Adding {} bits from {}".format(h, i)
            binform = int2bin(i-1, h)
            rolls += binform
            print rolls
            rolls_required -= 1
        except KeyboardInterrupt:
            print "Exiting"
            sys.exit()
        except:
            print "Failed to parse."
    # Turn into a key
    key = int(rolls, 2)
    print hex(key)[2:-1].upper()
    print "Entropy: {}".format(entropy(rolls))
