#!/usr/bin/env python
desc = "Calculates the standard deviation and average of input measurements."
import argparse
import khan_stat

parser = argparse.ArgumentParser(description=desc)
parser.add_argument('measurements', metavar="N", type=float, nargs="+")
parser.add_argument('--sample', dest='sample', action='store_true')
args = parser.parse_args()
print args.measurements

if args.sample:
  var_func = khan_stat.sample_variance
  stddev_func = khan_stat.sample_stddev
else:
  var_func = khan_stat.variance
  stddev_func = khan_stat.stddev

print "Average: ", khan_stat.average(args.measurements)
print "Variance: ", var_func(args.measurements)
print "Standard Deviation: ", stddev_func(args.measurements)
