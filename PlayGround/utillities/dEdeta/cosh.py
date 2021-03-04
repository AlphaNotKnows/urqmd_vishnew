from scipy.optimize import leastsq
from pylab import *
import numpy as np

central=[0,5,10,15,20,30,40,50,60,70]
urqmd_dir=sys.path[0]+'/dEdeta_urqmd'
QGP_dir=sys.path[0]+'/dEdeta_iSS'
id=0
data_urqmd=np.loadtxt(urqmd_dir+"/dEdeta{}~{}%.txt".format(central[id],central[id+1]))
data_QGP=np.loadtxt(QGP_dir+"/dEdeta{}~{}%.txt".format(central[id],central[id+1]))
eta=data_QGP[7:21,0]
dEdeta_urqmd=data_urqmd[7:21,1]
dEdeta_QGP=data_QGP[7:21,1]


xdata = eta
 
ydata = dEdeta_QGP


dEdeta = lambda x, alpha, beta: alpha * np.cosh(x-beta)
error =lambda p,y,x:np.abs(y-dEdeta(x,*p))
c, ret_val = leastsq(error, [600,-0.25], args=(ydata, xdata))
print(c)
print(ret_val)
plt.plot(eta,np.abs(dEdeta_QGP-dEdeta(eta,*c)))
plt.show()