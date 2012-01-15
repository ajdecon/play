import numpy
data = numpy.zeros((20,20),dtype=int)
f=open("data.txt",'r')

for r in range(20):
    vals = str.split(f.readline())
    for c in range(20):
        data[r][c] = int(vals[c])

maxval = 0
for r in range(3,20-3):
    for c in range(3,20-3):
        left = data[r][c] * data[r-1][c] * data[r-2][c] * data[r-3][c]
        right = data[r][c] * data[r+1][c] * data[r+2][c] * data[r+3][c]
        up = data[r][c] * data[r][c-1] * data[r][c-2] * data[r][c-3]
        down = data[r][c] * data[r][c+1] * data[r][c+2] * data[r][c+3]
        diag1 = data[r][c] * data[r+1][c+1] * data[r+2][c+2] * data[r+3][c+3]
        diag2 = data[r][c] * data[r-1][c+1] * data[r-2][c+2] * data[r-3][c+3]
        diag3 = data[r][c] * data[r-1][c-1] * data[r-2][c-2] * data[r-3][c-3]
        diag4 = data[r][c] * data[r+1][c-1] * data[r+2][c-2] * data[r+3][c-3]
        maxval = max((maxval,right,down,diag1,diag2,diag3,diag4))

print maxval


