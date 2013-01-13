#!/usr/bin/env python

def divisors(x):
    divs=[]
    for d in range(2,x/2):
        if x%d==0: divs.append(d)
    return divs

def is_abundant(x):
    if sum(divisors(x))>x: return True
    else: return False

def list_abundant(max_val):
    ab_nums=[]
    for x in range(max_val+1):
        if is_abundant(x): ab_nums.append(x)
        if x%100==0: print "now at %d" % (x)
    return ab_nums

la=list_abundant(28123)
print la
