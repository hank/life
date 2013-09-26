import binascii
import argparse
b58_digits = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'

parser = argparse.ArgumentParser()
parser.add_argument('key')
parser.add_argument('--tocustom', 
                    nargs=1, 
                    help="Custom version.  Not compatible with other options")
parser.add_argument('--toltc', action="store_true", help="Convert input to LTC private key")
parser.add_argument('--toftc', action="store_true", help="Convert input to FTC private key")
parser.add_argument('--tobtc', action="store_true", help="Convert input to BTC private key")
args = parser.parse_args()

if args.toltc:
    args.version = "176"
elif args.toftc:
    args.version = "142"
elif args.tobtc:
    args.version = "128"
elif args.tocustom:
    args.version = args.tocustom[0]

def base58_encode(n):
    l = []
    while n > 0:
        n, r = divmod(n, 58)
        l.insert(0,(b58_digits[r]))
    return ''.join(l)

def base58_decode(s):
    n = 0
    for ch in s:
        n *= 58
        digit = b58_digits.index(ch)
        n += digit
    return n

def packl(lnum, padmultiple=1):
    if lnum == 0:
        return b'\0' * padmultiple
    elif lnum < 0:
        raise ValueError("Can only convert non-negative numbers.")
    s = hex(lnum)[2:]
    s = s.rstrip('L')
    if len(s) & 1:
        s = '0' + s
    s = binascii.unhexlify(s)
    if (padmultiple != 1) and (padmultiple != 0):
        filled_so_far = len(s) % padmultiple
        if filled_so_far != 0:
            s = b'\0' * (padmultiple - filled_so_far) + s
    return s

def unpackl(bytestr):
    return int(binascii.hexlify(bytestr), 16) if len(bytestr) > 0 else 0
 

print "Input: ", args.key
decoded = base58_decode(args.key)
print "Input: ", hex(decoded)
binstr = packl(decoded)
print "Input: ", repr(binstr)
binstr = chr(int(args.version)) + binstr[1:]
print "Output: ", repr(binstr)
new_key = unpackl(binstr)
print "Output: ", base58_encode(new_key)
