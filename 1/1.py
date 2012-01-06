#!/usr/bin/env python

total = 0
for n in range(1000):
    if (n % 3 == 0) or (n % 5 == 0):
        total += n
print "Total = %d\n" % (total)
