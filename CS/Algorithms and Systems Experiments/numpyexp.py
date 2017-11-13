import numpy as np

n = 10

a1 = list(range(n))
a2 = np.arange(100)

if n<=100:
	print(a1)
	print(a2)

a = np.random.rand(5,4,3)
print(a.shape)
print(a.dtype)
print(a[:,2,:].shape)

