import numpy as np


A = np.array([[1,2,3,4,5],[1,2,3,4,5]])
v = np.array([1,2,3,4,5])

import numpy as np
count_output = np.empty(len(v),int)
for n in range(0,len(v)):
	count_output[n]=np.sum(A[:,n]==v[n])

print(count_output)
