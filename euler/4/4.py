#!/usr/bin/env python

import sys

def is_palindrome(number):
    string = str(number)
    for i in range(len(string)/2):
        if string[i]!=string[-(i+1)]:
            return False
    return True

# Test palindromes
#print is_palindrome(303)
#print is_palindrome(21)
#print is_palindrome(3467)
#print is_palindrome(9009)

# Find largest palindrome from product of two three-digit numbers
rmax = 999
rmin = 100
step = -1

max = 0
for x in range(rmax,rmin,step):
    for y in range(rmax,rmin,step):
        product = x*y
        if is_palindrome(product) and product>max:
            max = product
print "Biggest palindromic product is %d\n" % (max)
