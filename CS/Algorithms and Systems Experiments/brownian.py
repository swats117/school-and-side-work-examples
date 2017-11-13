from random import uniform, normalvariate
from time import sleep
import matplotlib.pyplot as pt


endpoints=[]
bumps = []

for j in range(1000):
	for i in range(10000):
		bumps.append(normalvariate(0,1))
	endpoints.append(sum(bumps))
	if j%50==0:
		print(j)

pt.hist(endpoints)
pt.show()

# pt.hist(bumps)
# pt.show()

# location=0
# path=[]
# for b in bumps:
# 	location+=b
# 	path.append(location)

# pt.plot(path)
# pt.show()

# # sleep(20)
# print(sum(bumps))

# pos=0
# path=[]
# for bump in bumps:
# 		path.append(pos)
# 		pos += bum
		
