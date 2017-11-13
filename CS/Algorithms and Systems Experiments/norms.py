import numpy as np
import matplotlib.pyplot as plt
global sum_norm
global norm_sum

def norm(vector, norm_val):
	vector = np.absolute(vector)
	vector = vector**norm_val
	v_sum = np.sum(vector);
	# print(vector)
	# print(v_sum)
	norm_val = v_sum**(1/norm_val)
	# print(norm_val)
	return norm_val



def makePlots(x,y,norm_val):


	fig, ax = plt.subplots()
	norm_x = norm(x,norm_val)
	norm_y = norm(y,norm_val)
	norm_xy = norm(x+y,norm_val)
	sum_norm.append(norm_xy)
	norm_sum.append(norm_x+norm_y)

	handles = []
	handles.append( ax.add_artist(plt.Circle((0, 0), norm_x, color='r', fill=False)) )
	handles.append( ax.add_artist(plt.Circle((x[0], x[1]), norm_y, color='b', fill=False)) )
	handles.append( ax.add_artist(plt.Circle((0, 0), norm_xy, color=(.9, 0.2, 0.9), fill=False )) )
	handles.append( ax.add_artist(plt.Circle((0, 0), norm_x+norm_y, color='g', fill=False )) )
	# print(ax)
	# print(fig)
	bound = max(norm_x+norm_y, (x[0]**2+x[1]**2)**(1/2)+norm_y )
	ax.set_xlim(-bound-.1,bound+.1)
	ax.set_ylim(-bound-.1,bound+.1)
	ax.set_aspect('equal')
	plt.arrow(0,0,x[0]+y[0],y[1]+x[1],length_includes_head=True, head_width=norm(x+y,2)/20)
	plt.arrow(0,0,x[0],x[1],length_includes_head=True, head_width=norm(x,2)/20)
	plt.arrow(x[0],x[1],(x[0]+y[0])-x[0],(y[1]+x[1])-x[1],length_includes_head=True, head_width=norm(x,2)/20)
	# handles, labels = ax.get_legend_handles_labels()
	# print(handles)
	labels = ['||x||_'+str(norm_val),'||y||_'+str(norm_val),'||x+y||_'+str(norm_val),'||x||+||y||_'+str(norm_val)]

	ax.legend(handles, labels)
	plt.show()
sum_norm=[]
norm_sum=[]
# a = np.array([-7,2])
# b = np.array([1,3])
# makePlots(a,b,1)
# makePlots(a,b,2)
# makePlots(a,b,5)
# makePlots(a,b,.5)
makePlots(x,y,1)
makePlots(x,y,2)
makePlots(x,y,5)
makePlots(x,y,.5)
sum_norm=np.array(sum_norm)
norm_sum=np.array(norm_sum)
# norm(a,3)
print("The green circle which represents ||x||+||y|| is greater than the pink which represents ||x+y|| circle for the 1,2, and 5 cases. The pink circle is greater than the green circle in the .5 case, so the triangle equality does not hold for p=0.5")


