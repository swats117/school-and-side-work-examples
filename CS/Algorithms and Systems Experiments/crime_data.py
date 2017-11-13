# import subprocess
import math
import json
import sys

import urllib.request
import time


# from mpl_toolkits.basemap import Basemap
# import matplotlib.pyplot as plt
# import numpy as np
 



def ret_url(lat,lon,radius):
  return 'http://api.spotcrime.com/crimes.json?lat='+str(lat)+'&lon='+str(lon)+'&key=privatekeyforspotcrimepublicusers-commercialuse-877.410.1607&radius='+str(radius)

allcrimes=[]



tes_coordinates = []
for i in range(29):
  if i%2==0:
      for j in range(7):
        tes_coordinates.append((j*2,i))
  else:
    for j in range(6):
        tes_coordinates.append((2*j+1,i))
    

# print(coordinates)
# tes_coordinates = [(0,0),(2,0),(4,0),(6,0),(1,1.5),(3,1.5),(5,1.5),(0,3),(2,3),(4,3),(6,3),(1,4.5),(3,4.5),(5,4.5),(0,6),(2,6),(4,6),(6,6),(1,7.5),(3,7.5),(5,7.5)]



# response = urllib.request.urlopen("http://api.spotcrime.com/crimes.json?lat=40.118312&lon=-88.243605&key=privatekeyforspotcrimepublicusers-commercialuse-877.410.1607&radius=1").read()
# jdata = json.loads(response)
# allcrimes.append(response["crimes"])

# response = subprocess.call(['curl','http://api.spotcrime.com/crimes.json?lat=40.118312&lon=-88.243605&key=privatekeyforspotcrimepublicusers-commercialuse-877.410.1607&radius=1'])
# response = requests.get(url)
# print(response)

latstep = 0.004
lonstep = 0.003

upperleftlat = 40.133740
upperleftlon = -88.276347

lowerrightlat = 40.083703
lowerrightlon = -88.190932

# coordinates=[]

for i in tes_coordinates:
  first = upperleftlat-i[0]*latstep
  second = (upperleftlon+i[1]*lonstep)

  # coordinates.append(str(first)+","+str(second))
  # print(ret_url(first,second,.5))
  print(str(first)+","+str(second))
  
  response = urllib.request.urlopen(ret_url(first,second,.02)).read()
  jdata = json.loads(response)
  [allcrimes.append(x) for x in jdata["crimes"]]

  # time.sleep(.2)
# sys.exit(1)
newlist = sorted(allcrimes, key=lambda k: k['cdid']) 
newnewlist = {v['cdid']:v for v in newlist}.values()
# print(newlist)
# sys.exit(1)
print("blah")

lookup_dict={"Arrest":0,"Arson":1,"Assault":2,"Burglary":3,"Robbery":4,"Shooting":5,"Theft":6,"Vandalism":7,"Other":8}

for x in newnewlist:
  
  print("["+str(x["lat"])+","+str(x["lon"])+","+str(lookup_dict[str(x["type"])])+"]")

print("blah")
print(newnewlist)

print(len(newnewlist))
# print(allcrimes)



londist=(lowerrightlon-upperleftlon)

# print(math.cos(math.radians(lowerrightlat))*69*)

print((upperleftlat-lowerrightlat)/6)
print((lowerrightlon-upperleftlon)/8)

print((upperleftlat-lowerrightlat)*69)


print(ret_url(upperleftlat,upperleftlon,3))
  