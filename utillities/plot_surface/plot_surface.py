import numpy as np
import matplotlib.pyplot as plt
data=np.loadtxt("/home/qinjian/research/simulation/UrqmdVishnu/utillities/plot_surface/surface.dat",dtype="float64")
print(data.shape)
print(data.size/7)
time=data[:,1]
R=data[:,4]
h=plt.hist2d(x=time,y=R,bins=50)
plt.colorbar(h[3])
plt.xlabel("t")
plt.ylabel(r"$\sqrt{x^2+y^2}$")
plt.title("PbPb 200GeV b=0. surface.dat")
plt.show()