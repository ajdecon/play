import sys
for a in range(1,32):
    for b in range(1,32):
        for c in range(1,32):
            if ((a*a + b*b + c*c) == 1000) and (a<b<c):
                print "a=%d, b=%d, c=%d" % (a,b,c)
                print "abc = %d" % (a*b*c)
                sys.exit()
