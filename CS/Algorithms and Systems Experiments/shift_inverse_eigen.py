import numpy as np
import numpy.linalg as la
import scipy.linalg as spla

matrix = np.array([[1,3,5],[5,2,0],[2,1,1]])
sigma = 1
matrix = matrix - sigma*np.eye(3)
P, L, U = spla.lu(matrix)

np.eye(3)


guess = np.array([np.sqrt(1/3),np.sqrt(1/3),np.sqrt(1/3)])

for i in range(500):
	guess = P.T @ guess
    guess = spla.solve_triangular(L,guess,lower=True)
    guess = spla.solve_triangular(U,guess,lower=False)
    # guess = la.solve(matrix,guess)
    guess = guess/la.norm(guess)


print(guess)

print(guess@(matrix@guess)/guess@guess)