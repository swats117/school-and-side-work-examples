import numpy as np
import scipy.misc as scm
import matplotlib.pyplot as plt




x=1
desired_rel_error=1

less_than=(desired_rel_error*np.exp(x))/(100)
inc=1
N = 0
while True:
    if((x**inc)/scm.factorial(inc,True)<less_than):
        N=inc-1
        break
    inc += 1




exp_approx = np.full((10,),x)
blah = np.array(list(range(10)))
fact = scm.factorial(blah,True)
exp_approx=(exp_approx**blah)/fact
running_sum=0
for x in range(len(exp_approx)):
	running_sum += exp_approx[x]
	exp_approx[x]=running_sum
print(exp_approx)
plt.plot(blah,exp_approx)
plt.plot(N)
plt.title("approximation of e^x at various finite series length from infinite series")
plt.xlabel("length of series")
plt.ylabel("value of e")
plt.show()

