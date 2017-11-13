a=366.6000000001
temp = a
print(temp)
k=0
for x in range(-1,-373,-1):
    temp2 = temp
    if(a==(temp2-2**x)):
        k=x+1
        print(k)
        break
