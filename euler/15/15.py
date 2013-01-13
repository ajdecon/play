#!/usr/bin/env python26

# This problem really doesn't require much programming to solve.
# Assume that the linear distance to cover is 40; this will not be
# changed regardless of route. We have only 2 actions we can take at any
# given time (down and right), and we need exactly 20 downs and 20 rights.
# So the number of possible routes is equal to the number of possible
# sequences of 20 downs and 20 rights.

# This is a permutation problem of two sets of 20 identical objects, call
# them D and R. So the answer is 40!/(20!*20!)

# Since this is a programming problem, however...

import math
print math.factorial(40)/(math.factorial(20)*math.factorial(20))
