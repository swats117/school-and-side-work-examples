import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return 1/(1+25*(x**2))

degree_arr=[4,6,16]
solutions = []

for n in range(len(degree_arr)):
    x_coord = np.linspace(-1,1,degree_arr[n])
    y_coord = f(x_coord)
    Vandermonde_matrix = np.empty((degree_arr[n],degree_arr[n]))
    
    for i in range(degree_arr[n]):
        Vandermonde_matrix[:,i] = x_coord**i
    solutions.append(np.linalg.solve(Vandermonde_matrix, y_coord))
    
coefficients_3 = solutions[0]
coefficients_5 = solutions[1]
coefficients_15 = solutions[2]


testpoints = np.linspace(-1,1,51)
    
# print(np.flip(solutions[0],0))

plt.plot(testpoints,f(testpoints),label='F(x)')
for i in range(len(solutions)):
    plt.plot(testpoints, np.polyval(np.flip(solutions[i],0), testpoints), label='Interpolation Degree '+str(degree_arr[i]-1))
    
plt.title('Plot of a Function vs its Interpolation of Varying Degrees')
plt.legend(loc="best")

plt.show()