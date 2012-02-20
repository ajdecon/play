#!/usr/bin/env python

# Get the data
data = open("triangle.txt","r")
rows = []
for line in data:
    rows.append([int(x) for x in line.split()])
data.close()

# In-place reduction of the triangle
#   For each element in the second-to-last row, add the max value
#   of the two adjacent elements in the last row. Then remove the
#   last row. Repeat as long as there is more than one row.
while len(rows)>1:
    for i in xrange(len(rows)-1):
        rows[-2][i] += max(rows[-1][i:i+2])
    del rows[-1]

print rows[0][0]
