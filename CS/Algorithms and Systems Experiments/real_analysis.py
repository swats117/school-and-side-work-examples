def blah(x):

	return (2+x)/(5+2*x)

current = 1/2
for i in range(11):
	print(blah(current))
	current = blah(current)
