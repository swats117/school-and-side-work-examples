import numpy as np

markov = np.array([\
    [.7, .1, .1, .1],\
    [0, .5, .4, .1],\
    [0, .8, .1, .1],\
    [0, 0, 0, 1]
    ])
current = np.array([1,0,0,0])
hours = 0;
while current[3]<.95:
    hours+=1
    current = markov.T @ current
    print(current)