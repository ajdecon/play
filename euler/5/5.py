#!/usr/bin/env python

# Problem 5: What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

def check(n):
    list=range(1,20)
    for d in list:
        if not (n%d==0):
            return False
    return True


x = 19*20
while not check(x):
    x = x+20
print "Final answer! x = %d\n" % (x)
