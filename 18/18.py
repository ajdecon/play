#!/usr/bin/env python

# Triangle with 15 rows. Row 0 = 1 number. Each row = 1 more item.
# Each item can point to the item on the
# next row with the same index, or index + 1.

# Get the data
data = open("data.txt","r")
rows = []
for line in data:
    rows.append([int(x) for x in line.split()])
data.close()

# Algorithm:
#   For each row:
#       For each path:
#           Check: is this path still valid?
#           If so: move forward in 2 dirctions
#           If not: remove path from list
# How do we know it's valid?
max_per_row = 99
paths = [ [0] ]
path_sums = [rows[0][0]]
total_rows = len(rows)
current_max = 0

for r in range(14):
    print "******** Level %d" % (r)
    new_paths = []
    new_path_sums = []
    for p in range(len(paths)):
        current_path = paths[p]
        current_sum = path_sums[p]
        if (total_rows-r-1)*max_per_row<(current_max-current_sum): # It's impossible to match the current max
            print "=================="
            print "Killed this path:"
            print current_path
            print "=================="
            continue # Do not put this path back in the mix
        else:
            new_path_1 = current_path[:]
            new_path_1.append( current_path[len(current_path)-1] ) # Move to same index
            new_path_sum_1 = current_sum + rows[r+1][ new_path_1[len(new_path_1)-1] ]
            new_paths.append(new_path_1)
            new_path_sums.append(new_path_sum_1)
            print "**** Added path:"
            print new_path_1
            print new_path_sum_1

            new_path_2 = current_path[:]
            new_path_2.append( current_path[len(current_path)-1]+1 )
            new_path_sum_2 = current_sum + rows[r+1][ new_path_2[len(new_path_2)-1] ]
            new_paths.append(new_path_2)
            new_path_sums.append(new_path_sum_2)
            print "**** Added path:"
            print new_path_2
            print new_path_sum_2
    paths = new_paths
    path_sums = new_path_sums
    current_max = max(path_sums)

print "Max is %d" % (current_max)
print "Path is:"
print paths[path_sums.index(current_max)]
