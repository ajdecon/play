#!/usr/bin/env python26
# Find sum of digits of 100!
import math
print sum([int(d) for d in str(math.factorial(100))])
