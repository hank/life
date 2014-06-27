import binascii, argparse, struct, sys

def int2bin(n, count):
    """returns the binary of integer n, using count number of digits"""
    return "".join([str((n >> y) & 1) for y in range(count-1, -1, -1)])

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
    print "{} is the divisor".format(2**h)
    rolls = ""
    rolls_required = 256/h
    print "Input {} dice rolls:".format(rolls_required)
    while rolls_required > 0:
        try:
            i = raw_input("Roll ({} left): ".format(rolls_required))
            print "Adding {} bits from {}".format(h, (int(i) % 2**h))
            binform = int2bin(int(i) % 2**h, h)
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
