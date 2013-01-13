#!/usr/bin/env python

import math
import sys

def isprime(n):
    if (n%2==0) or (n%3)==0:
        return false
    limit = math.sqrt(float(n))
    k = 1
    while (k<limit):
        c1 = 6*k-1
        c2 = 6*k+1
        if (n%c1==0) and (c1!=n):
            return False
        if (n%c2==0) and (c2!=n):
            return False
        k=k+1
    return True


n = 600851475143
d = math.floor(math.sqrt(float(n)))
if (d%2==0): d=d-1
while d>2:
    if (n%d==0) and (isprime(d)):
        print "largest prime factor = %d\n" % (d)
        sys.exit()
    if (d%2000==0):
        print "d = %d\n" % (d)
    d=d-2

