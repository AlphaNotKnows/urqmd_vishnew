import numpy as np
import matplotlib.pyplot as plt

PHOBOS=np.loadtxt("/home/qinjian/research/simulation/urqmd_vishnew/utillities/dNdy/central_AuAu200.txt")
central=PHOBOS[:,0]
ex_p=PHOBOS[:,1]
error_p=PHOBOS[:,2]
ex_pi=PHOBOS[:,3]
error_pi=PHOBOS[:,4]
ex_K=PHOBOS[:,5]
error_K=PHOBOS[:,6]

fig=plt.figure()
ax=fig.add_axes([0.1,0.1,0.8,0.8])
ax.errorbar(central,ex_p,yerr=error_p,label='PHOBOS p',fmt='o',ms=2)
ax.errorbar(central,ex_pi,yerr=error_pi,label='PHOBOS pi',fmt='o',ms=2)
ax.errorbar(central,ex_K,yerr=error_K,label='PHOBOS K',fmt='o',ms=2)
ax.set_yscale('log')


data=np.loadtxt("/home/qinjian/research/simulation/urqmd_vishnew/utillities/dNdy/dNdeta0_0.28_1.0.txt")
p=data[:,2]
pi=data[:,4]
K=data[:,6]
ax.plot(central,p,label='p')
ax.plot(central,pi,label='pi')
ax.plot(central,K,label='K')

ax.legend()
ax.set_title("Edec=1GeV")
plt.show()