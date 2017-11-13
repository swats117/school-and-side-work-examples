#Given an array of numbers A, produce an array such that
# A_1 < A_2 > A_3 < A_4 > A_5 < A_6 > A_7 < A_8

import numpy as np

n=10

numbers = np.random.rand(n)
print(numbers)

for i in range(n-1):
	if (i & 1) == 0:
		if numbers[i]<numbers[i+1]:
			numbers[i], numbers[i+1] = numbers[i+1], numbers[i]
	else:
		if numbers[i]>numbers[i+1]:
			numbers[i], numbers[i+1] = numbers[i+1], numbers[i]

print(numbers)




