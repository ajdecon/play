#!/usr/bin/env python

# Get the number to check
f = open("check-number.txt","r");
longnum = f.readline()
nums = []

for i in range(1000-4):
    nums.append(longnum[i:i+5])

count = len(nums)
max = 0
for i in range(count-1):
    now = int(nums[i])*int(nums[i+1])
    if now>max:
        max = now

print max
