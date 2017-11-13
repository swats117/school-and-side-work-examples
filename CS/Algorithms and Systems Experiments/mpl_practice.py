import numpy as np
import matplotlib.pyplot as plt

a=5
k=3

xvalues = np.linspace(1.1,10,20)
yvalues = []
for value in xvalues:
    yvalues.append(a*np.random.uniform(4/5*value, 6/5*value)**k)

perfect_x = np.linspace(1.1,10,1000)
perfect_y = a*perfect_x**k

plt.semilogy(xvalues,yvalues)
plt.semilogy(perfect_x,perfect_y)   
plt.show()

import numpy as np
max_val=np.amax(A)
min_val=np.amin(A)
max_index=None
min_index=None
for index in range(0,len(A)):
    if A[index]==max_val:
        max_index=index
    if A[index]==min_val:
        min_index=index

import numpy as np

average = np.sum(A)/len(A)

std_val = (np.sum((A-average)**2)/len(A))**(1/2)