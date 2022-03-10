import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

angle_1=np.linspace(0,90,10)*np.pi/180
angle_2= np.linspace(-60,30,10)*np.pi/180
angle_3=np.linspace(40,85,10)*np.pi/180

distance_1=[22.71,16.09,12.74,10.96,9.67,9.10,8.75,8.53,8.80,9.33]
distance_2=[5.89,5.59,5.67,5.71,5.87,5.85,6.92,7.68,9.74,13.13]
distance_3=[22.31,18.71,17.61,14.97,11.82,13.06,10.94,10.84,11.12,9.31]

fit_1=np.polyfit(angle_1,distance_1,1)
fit_2=np.polyfit(angle_2,distance_2,1)
fit_3=np.polyfit(angle_3,distance_3,1)

fig, ax = plt.subplots(2,1,subplot_kw={'projection': 'polar'},figsize=(10,10))
ax[0].scatter(angle_1,distance_1,c='royalblue',label="measurements 1", marker='o')
ax[0].scatter(angle_3, distance_3, c='orangered', label="measurements 3",marker='o')
ax[0].scatter(angle_2, distance_2, c='lime', label="measurements 2",marker='o')

ax[1].scatter(angle_2,np.multiply(angle_2,fit_2[0])+fit_2[1], c='lime', label="fit 2",marker='x')
ax[1].scatter(angle_1,np.multiply(angle_1,fit_1[0])+fit_1[1],c='royalblue', label="fit 1",marker='x')
ax[1].scatter(angle_3,np.multiply(angle_3,fit_3[0])+fit_3[1],c='orangered', label="fit 3",marker='x')
#plt.xlabel("angle")
#plt.ylabel("distance")
fig.legend(loc="lower center",ncol=2)
plt.show()
