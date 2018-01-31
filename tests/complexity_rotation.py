# -*- coding: utf-8 -*-
"""
Created on Wed Jan 31 12:04:33 2018

@author: TMP-Couderc
"""

import matplotlib.pyplot as plt
from pylab import linspace, meshgrid
import numpy as np
from mpl_toolkits.mplot3d.axes3d import Axes3D
from matplotlib import cm

    
def fic_to_tab_square(fichier):
    fichier = "/home/T/TMP-Couderc/Digital-analysis/bild/" + fichier
    fic = open(fichier, "r")
    tab_n = []
    tab_t1 = []
    tab_t2 = []
    tab_n = np.array(tab_n)
    tab_t1 = np.array(tab_t1)
    tab_t2 = np.array(tab_t2)
    for line in fic.readlines():
        tmp = line.split()
        if tmp != []:
            if int(tmp[0])==int(tmp[1]):
                tab_n = np.append(tab_n, [int(tmp[0])])
                tab_t1 = np.append(tab_t1, [float(tmp[2])*10**7])
                tab_t2 = np.append(tab_t2, [float(tmp[3])*10**7])
    fic.close()
    return tab_n, tab_t1, tab_t2



n,t1,t2 = fic_to_tab_square("compare_bicubic_bilenear.txt")
#y1 = 15*15*n*n/100000000
#y2 = (6*n*np.log(2*n)+n*n)/10000000
p1, = plt.plot((n),(t1))
p2, = plt.plot((n),(t2))
n2 = [i for i in range(3,3600)]
#n3 = [i*i*np.log(i) for i in n2]
#n4 = [i*i for i in n2]
#p4, = plt.plot(np.log2(n2),np.log2(n3))
#p5, = plt.plot(np.log2(n2),np.log2(n4))
plt.title("Logarithmic scale : comparaison from dest and to source ")
plt.legend([p1, p2], ["to_dest", "from_source"], loc = "best")
plt.ylabel("Number of computations (log2)")
plt.xlabel("Matrix dimension (log2)")
plt.show()