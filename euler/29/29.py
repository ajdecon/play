#!/usr/bin/env python

terms=[]
for a in range(2,101):
    for b in range(2,101):
        c=a**b
        if not c in terms:
            terms.append(c)
print len(terms)
