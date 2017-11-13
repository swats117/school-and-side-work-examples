import numpy as np

titles = ["A","B","C","D"]
links =[[1,2,3],[3],[0,3],[1]]

initial_state=np.array([.25,.25,.25,.25])

import numpy as np

def test_state(old_state, new_state):
    # print(new_state)
    error = np.amax(np.absolute(old_state - new_state))
    if error <= 10**-9:
        return False
    else:
        return True

def get_next_state(links, current):
    next_state = np.zeros(current.shape)
    # print(next_state)
    for i in range(len(current)):
        fraction = len(links[i])+1
        # fraction = len(links[i])
        for j in links[i]:
            next_state[j] += current[i]/fraction
        next_state[i]+=current[i]/fraction
    return next_state

first_state = get_next_state(links,initial_state)
# print(first_state)

old_state = initial_state
current_state = first_state
while test_state(old_state,current_state):
    old_state = current_state
    current_state = get_next_state(links,current_state)


page_rankings = [(title,rank) for rank,title in sorted(zip(current_state,titles))]
page_rankings = page_rankings[0,50]
print(page_rankings)






#