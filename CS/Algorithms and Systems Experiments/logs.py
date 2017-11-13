import numpy as np
import math


a = [math.ceil(x*math.log(float(x),2)) for x in range(1,200)]
prev = np.array([0]+a[:len(a)-1])

output = a-prev

print([(i,output[i]) for i in range(len(output))])

for i in range(1,100):
	n = 94*2**i
	print(math.ceil(n*math.log(n,2))-math.ceil((n-1)*math.log((n-1),2)))

