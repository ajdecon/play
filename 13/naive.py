# Initial version; brute force problem 13

# Get the 100 big numbers and sum them
sum = long(0)
f = open("data.txt","r")
for line in f:
    sum += long(line)
digits = str(sum)
answer = ''.join([digits[i] for i in range(10)])
print answer
    
