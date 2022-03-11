import matplotlib.pyplot as plt
import numpy as np
import sys

#circles with position x,y and radious r
circle_1=[float(sys.argv[1]),float(sys.argv[2]),float(sys.argv[3])]
circle_2=[float(sys.argv[4]),float(sys.argv[5]),float(sys.argv[6])]
circle_3=[float(sys.argv[7]),float(sys.argv[8]),float(sys.argv[9])]

# circle_1 = [0.0,0.0,9.107]
# circle_2 = [16.0,0.0,22.121]
# circle_3 = [0.0,16.0,24.260]

# The point of intersection calculated in the c program
intersection = [float(sys.argv[10]),float(sys.argv[11])]

#intersection =[-4.7,-7.8]

limit_x=max(circle_1[0],circle_2[0],circle_3[0])+max(circle_1[2],circle_2[2],circle_3[2])+1
limit_y=max(circle_1[1],circle_2[1],circle_3[1])+max(circle_1[2],circle_2[2],circle_3[2])+1

fig, ax = plt.subplots(1,1,figsize=(10,10))
ax.add_patch(plt.Circle((circle_1[0],circle_1[1]),circle_1[2],alpha=0.5,edgecolor='lime',fill=0))
ax.add_patch(plt.Circle((circle_2[0],circle_2[1]),circle_2[2],alpha=0.5,edgecolor='blue',fill=0))
ax.add_patch(plt.Circle((circle_3[0],circle_3[1]),circle_3[2],alpha=0.5,edgecolor='tomato',fill=0))
ax.add_patch(plt.Circle((intersection[0],intersection[1]),0.5,color='red',fill=1))
ax.grid(True)

plt.xlim(-limit_x,limit_x)
plt.ylim(-limit_y,limit_y)
plt.show()
