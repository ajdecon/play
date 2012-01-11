#!/usr/bin/env python

# Get the number to check
f = open("check-number.txt","r");
x = f.readline()

maxnum = 0
for i in range(1000-4):
    prod = int(x[i])*int(x[i+1])*int(x[i+2])*int(x[i+3])*int(x[i+4])
    if prod>maxnum:
        maxnum=prod

print maxnum

