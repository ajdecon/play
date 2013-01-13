#!/usr/bin/env python

def do_seq(x):
    count = 0
    while True:
        count +=1
        if x==1:
            return count
        if x%2==0:
            x=x/2
        else:
            x=(3*x)+1

# Find longest sequence starting under 1,000,000
mchain = 0
mstart = 2
for x in range(2,999999):
    chain = do_seq(x)
    if (chain>mchain):
        mchain=chain
        mstart=x
    if (x%10000==0):
        print "Currently on starting value %d" % (x)

print "Maximum chain starts on %d and has length %d" % (mstart,mchain)

