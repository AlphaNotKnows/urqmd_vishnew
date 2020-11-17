import numpy as np
import matplotlib.pyplot as plt
central=[0,3,6,10,15,20,25]
for i in range(len(central)-1):
  input_path="/home/qinjian/research/simulation/UrqmdVishnu/utillities/dNdy/DNDY/dNdeta{}~{}%.txt".format(central[i],central[i+1])
  data=np.loadtxt(input_path)
  data=data[4:20,:]
  eta=data[:,0]
  dNdeta=data[:,1]
  plt.subplot(2,3,6-i)
  plt.plot(eta,dNdeta,label="{}~{}%".format(central[i],central[i+1]))
  plt.legend(fontsize=8)
  plt.xticks(fontsize=8)
  plt.yticks(np.arange(0,max(dNdeta)+50,100),fontsize=8)
  # plt.xlabel(r"$\eta$")
  # plt.ylabel(r"$dN/d\eta$")
# plt.legend()
plt.show()
