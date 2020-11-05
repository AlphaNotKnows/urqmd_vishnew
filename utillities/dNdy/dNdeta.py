import numpy as np
import matplotlib.pyplot as plt
central=[0,3]
for i in range(len(central)-1):
  input_path="/home/qinjian/research/simulation/UrqmdVishnu/utillities/dNdy/dNdeta/dNdeta{}~{}%.txt".format(central[i],central[i+1])
  data=np.loadtxt(input_path)
  data=data[4:20,:]
  eta=data[:,0]
  dNdeta=data[:,1]
  plt.plot(eta,dNdeta,label="{}~{}%".format(central[i],central[i+1]))
plt.xlabel(r"$\eta$")
plt.ylabel(r"$dN/d\eta$")
plt.legend()
plt.show()
