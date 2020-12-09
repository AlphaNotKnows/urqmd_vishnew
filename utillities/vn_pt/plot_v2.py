import numpy as np
import matplotlib.pyplot as plt

v2=np.loadtxt('/home/qinjian/research/simulation/urqmd_vishnew/utillities/vn_pt/101_v2_AuAu200.txt')
pT=np.linspace(0,3.,30)
plt.plot(pT,v2,label=r'$\pi$')
plt.ylim(0,0.4)
plt.title("AuAu200GeV 20~30%")
plt.legend()
plt.show()