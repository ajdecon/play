
# recursive fibonacci numbers
def recursive_fib(n):
    if n==0: return 0
    if n==1: return 1
    return recursive_fib(n-1) + recursive_fib(n-2)

# non-recursive fib
def fib(n):
    if n==0: return 0
    f=[]
    f.append(0)
    f.append(1)
    for i in range(2,n+1):
        f.append(f[i-1]+f[i-2])
    return f[n]
