#!/usr/bin/env python

def is_palindrome(number):
    string = str(number)
    for i in range(len(string)/2):
        if string[i]!=string[-(i+1)]:
            return False
    return True

# Test palindromes
print is_palindrome(303)
print is_palindrome(21)
print is_palindrome(3467)
print is_palindrome(9009)
