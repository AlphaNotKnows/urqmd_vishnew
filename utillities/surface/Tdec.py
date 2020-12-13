import numpy as np
import matplotlib.pyplot as plt
import sys

data=np.loadtxt(sys.path[0]+"/results/decdat2.dat")
Edec=data[:,6]
Tdec=data[:,8]
BAMU=data[:,9]
SMU=data[:,10]
print(Edec)
print(Tdec.max())
print(Tdec.min())
print(BAMU.max())
print(BAMU.min())
print(SMU.max())
print(SMU.min())