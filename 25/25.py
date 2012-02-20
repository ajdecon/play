#!/usr/bin/env python

fib=[1,1]
while len(str(fib[-1]))<1000:
    fib.append(fib[-1]+fib[-2])
print len(fib)
print len(str(fib[-1]))
print fib[-1]
