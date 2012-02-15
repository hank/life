# Special Khan Academy rounding average function
# Rounds to the first decimal place
def average(s):
  return round(sum(s)/len(s), 1)

# Normal variance function
def variance(s):
  avg = average(s)
  return sum([(x-avg)**2 for x in s])/len(s)

# Sample variance function
# Adjusts for sample bias
def sample_variance(s):
  avg = average(s)
  return sum([(x-avg)**2 for x in s])/(len(s)-1)

# Special Khan Academy rounding stddev function
# Rounds to the first decimal place
def stddev(s):
  return round(variance(s)**(1./2), 1)
  
def sample_stddev(s):
  return round(sample_variance(s)**(1./2), 1)
