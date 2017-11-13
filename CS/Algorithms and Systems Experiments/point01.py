from time import sleep

x = 0.0

while x != 1.0:
	x += 0.1
	print(repr(x))

	sleep(0.1)
