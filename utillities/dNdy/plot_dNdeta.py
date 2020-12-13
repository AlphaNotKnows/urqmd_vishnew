import numpy as np
import matplotlib.pyplot as plt

PHINIX=np.loadtxt("/home/qinjian/research/simulation/urqmd_vishnew/utillities/dNdy/central_AuAu200.txt")
central=PHINIX[:,0]
ex_p=PHINIX[:,1]
error_p=PHINIX[:,2]
ex_pi=PHINIX[:,3]
error_pi=PHINIX[:,4]
ex_K=PHINIX[:,5]
error_K=PHINIX[:,6]

fig=plt.figure()
ax=fig.add_axes([0.1,0.1,0.8,0.8])
ax.errorbar(central,ex_p,yerr=error_p,label='PHINIX p',fmt='o',ms=2)
ax.errorbar(central,ex_pi,yerr=error_pi,label='PHINIX pi',fmt='o',ms=2)
ax.errorbar(central,ex_K,yerr=error_K,label='PHINIX K',fmt='o',ms=2)
ax.set_yscale('log')


data=np.loadtxt("/home/qinjian/research/simulation/urqmd_vishnew/utillities/dNdy/dNdeta0_0.28_1.0.txt")
p=data[:,2]
pi=data[:,4]
K=data[:,6]
ax.plot(central,p,label='p Edec=1.0')
ax.plot(central,pi,label='pi Edec=1.0')
ax.plot(central,K,label='K Edec=1.0')

data=np.loadtxt("/home/qinjian/research/simulation/urqmd_vishnew/utillities/dNdy/dNdeta0_0.3_0.25.txt")
p=data[:,2]
pi=data[:,4]
K=data[:,6]
ax.plot(central,p,label='p Edec=0.25')
ax.plot(central,pi,label='pi Edec=0.25')
ax.plot(central,K,label='K Edec=0.25')

ax.legend()
plt.show()