import numpy
data = numpy.zeros((20,20),dtype=int)
f=open("data.txt",'r')

for r in range(20):
    vals = str.split(f.readline())
    for c in range(20):
        data[r][c] = int(vals[c])

print data

