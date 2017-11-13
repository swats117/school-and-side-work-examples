import numpy as np
import scipy.linalg as spla

A=np.array([[2,3],[4,5]])

P, L, U = spla.lu(A)


P_transpose = P.T

print(P_transpose)
pivots = np.array([])
print(len(P_transpose))
for row in range(len(P_transpose)):
	print(row)
	print(P_transpose[row])
	for col in range(len(P_transpose[row])):
		print("col",col)
		if P_transpose[row][col]==1.0 :
			print("is one")
			pivots = np.append(pivots,col)

print(pivots)


P_transpose = P.T

pivots = np.array([])
for row in range(len(P_transpose)):
	for col in range(len(P_transpose[row])):
		if P_transpose[row][col]==1.0 :
			pivots = np.append(pivots,col)

