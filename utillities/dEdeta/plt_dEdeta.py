import numpy as np
import matplotlib.pyplot as plt
import os
import sys

central=[0,5,10,15,20,30,40,50,60,70]
urqmd_dir=sys.path[0]+'/dEdeta_urqmd'
QGP_dir=sys.path[0]+'/dEdeta_iSS'
# n=3
# fig,ax=plt.subplots(n,n)
# for i in range(0,n):
#   for j in range(0,n):
#     id=3*i+j
#     data_urqmd=np.loadtxt(urqmd_dir+"/dEdeta{}~{}%.txt".format(central[id],central[id+1]))
#     data_QGP=np.loadtxt(QGP_dir+"/dEdeta{}~{}%.txt".format(central[id],central[id+1]))
#     eta=data_QGP[:,0]
#     # ax[i,j].set_yscale("log")
#     dEdeta_urqmd=data_urqmd[:,1]
#     dEdeta_QGP=data_QGP[:,1]
#     ax[i,j].plot(eta,dEdeta_urqmd)
#     ax[i,j].plot(eta,dEdeta_QGP)
#     ax[i,j].legend(["urqmd{}~{}%".format(central[id],central[id+1]),"QGP{}~{}%".format(central[id],central[id+1])],fontsize=5)
#     ax[i,j].tick_params(labelsize=5)
#     ax[i,j].tick_params(labelsize=5)
#     if j==0:
#       ax[i,j].set_ylabel(r"$dE/d\eta$",fontsize=5)
#     if i==2:
#       ax[i,j].set_xlabel(r"$\eta$",fontsize=5)
# plt.show()
for id in range(0,2):
  plt.subplot(2,1,id+1)
  data_urqmd=np.loadtxt(urqmd_dir+"/dEdeta{}~{}%.txt".format(central[id],central[id+1]))
  data_QGP=np.loadtxt(QGP_dir+"/dEdeta{}~{}%.txt".format(central[id],central[id+1]))
  eta=data_QGP[:,0]
  dEdeta_urqmd=data_urqmd[:,1]
  dEdeta_QGP=data_QGP[:,1]
  print(dEdeta_QGP)
  print(eta)
  plt.plot(eta,dEdeta_urqmd,label="urqmd")
  plt.plot(eta,dEdeta_QGP,label="hydro")
  plt.xlabel(r"$\eta$")
  plt.ylabel(r"$dE/d\eta$")
plt.legend()
plt.savefig(sys.path[0]+"/iSS.png")