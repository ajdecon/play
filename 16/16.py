#!/usr/bin/env python
import math
digits = str(int(math.pow(2,1000)))
total=0
for d in digits:
    total+=int(d)
print total
