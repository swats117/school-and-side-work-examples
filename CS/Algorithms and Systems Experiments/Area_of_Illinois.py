import scipy.misc
img = scipy.misc.imread('illinois_bw.png')
import numpy as np

num_rows, num_cols = img.shape


trials = 10**3
col_points = np.empty((trials),dtype="int")
row_points = col_points.copy()
for i in range(trials):
    col_points[i] = np.random.randint(0,num_cols)
    row_points[i] = np.random.randint(0,num_rows)

print(col_points,row_points)

points = img[row_points,col_points]

box_area = 304*450

area = np.count_nonzero(points==0)/trials * box_area
real_area = np.count_nonzero(img==0)/img.size*box_area

rel_error= abs((real_area-area)/real_area)
print(box_area,area,real_area,rel_error)