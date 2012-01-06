#!/usr/bin/env python

a=1
b=2
total=0
max=4000000

while b<max:
    if (b%2==0):
        total+=b
    c=b+a
    a=b
    b=c

print "total = %d" % (total)
