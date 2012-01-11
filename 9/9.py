import sys
import math

for a in range(1,1000):
    for b in range(1,1000):
        c = math.sqrt(a*a+b*b)
        if (a+b+c==1000):
            print "a=%d, b=%d, c=%d" % (a,b,c)
            print "abc = %d" % (a*b*c)
            sys.exit()
