import numpy as np
import matplotlib.pyplot as plt

prob_n = np.empty(99)
perc_50 = []
for n in range(2,101):
	positives = 0
	for i in range(1,1000):
		birthdays = np.random.randint(1,365,n)
		if len(birthdays) > len(np.unique(birthdays)):
			positives += 1
	prob_n[n-2]=positives/1000

for i in range(0,len(prob_n)):
	if prob_n[i] > .5:
		perc_50=i
		break

# print(prob_n)
# print(perc_50)


plt.plot(list(range(2,101)),prob_n)
plt.ylabel('Probability of two People Having the Same Birthday')
plt.xlabel('Number of People in the Room')
plt.title('Probability that at Least 2 People in Room of n People Share a Birthday')
plt.show()

