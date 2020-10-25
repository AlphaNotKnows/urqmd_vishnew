import numpy as np
import matplotlib.pyplot as plt
data=np.loadtxt("/home/qinjian/research/simulation/UrqmdVishnu/utillities/results/dNchdy.dat")
y=data[:,0]
dNdy=data[:,1]
plt.plot(y,dNdy)
plt.xlabel("rapidity")
plt.ylabel("dN/dy")
plt.title("dN/dy of AuAu 200GeV 0~6%")
plt.show()