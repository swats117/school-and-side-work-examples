# i ← 1
# while i < length(A)
#     x ← A[i]
#     j ← i - 1
#     while j >= 0 and A[j] > x
#         A[j+1] ← A[j]
#         j ← j - 1
#     end while
#     A[j+1] ← x[4]
#     i ← i + 1
# end while


def insertionSort(A):
	swapCount=0

	i=1
	while i<len(A):
		x = A[i]
		j = i -1
		while j >= 0 :
			A[j+1]=A[j]
			swapCount+=1
			j = j-1
		A[j+1] = x
		print(A)
		i = i+1
	return swapCount

result = insertionSort([4,3,2,1])
print(result)

def bogiSort(A):

	if len(A)<=16:
		insertionSort(A);









