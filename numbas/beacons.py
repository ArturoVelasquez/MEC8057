import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

#circles with position x,y and radious r
circle_1 = [0.0,0.0,9.107]
circle_2 = [16.0,0.0,22.121]
circle_3 = [0.0,16.0,24.260]

limit_x=max(circle_1[0],circle_2[0],circle_3[0])+max(circle_1[2],circle_2[2],circle_3[2])
limit_y=max(circle_1[1],circle_2[1],circle_3[1])+max(circle_1[2],circle_2[2],circle_3[2])

fig, ax = plt.subplots(1,1,figsize=(10,10))
ax.add_patch(plt.Circle((circle_1[0],circle_1[1]),circle_1[2],alpha=0.5,color='lime',fill=0))
ax.add_patch(plt.Circle((circle_2[0],circle_2[1]),circle_2[2],alpha=0.5,color='blue',fill=0))
ax.add_patch(plt.Circle((circle_3[0],circle_3[1]),circle_3[2],alpha=0.5,color='tomato',fill=0))
#fig.legend(loc="lower center",ncol=2)
plt.xlim(-limit_x,limit_x)
plt.ylim(-limit_y,limit_y)
plt.show()
