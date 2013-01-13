#!/usr/bin/env python

# 17.py: count the characters when the numbers in 1-1000 inclusive are written in words.
#        Count only letters, not other characters.

from num2word_EN_GB import to_card
import re
pattern = re.compile("[a-z]")
total_chars=0
for x in range(1,1001):
    w = to_card(x)
    local_count = 0
    for c in w:
        if pattern.match(c):
            local_count+=1
        print "'%s' - %d" % (c,local_count)
    print "%d = %s: %d" % (x,w,local_count)
    total_chars+=local_count

print "Total number of characters: %d " % (total_chars)
