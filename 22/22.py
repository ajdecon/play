#!/usr/bin/env python26
import time

f = open("names.txt","r")
names=[]
for n in f:
    names.append(n.lower())
names = sorted(names)

i=0
total=0
for name in names:
    i+=1
    score=0
    for c in name:
        if c!="\n":
            score += ord(c)-96
    score=score*i
    total += score

print "total name score is %d" % (total)
