#!/usr/bin/env python

# Triangle with 15 rows. Row 0 = 1 number. Each row = 1 more item.
# Each item can point to the item on the
# next row with the same index, or index + 1.

# Get the data
data = open("data.txt","r")
rows = []
for line in data:
    rows.append([int(x) for x in line.split()])

