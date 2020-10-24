#!/usr/bin/env python3

import argparse
import collections
import re
import math
import numpy as np
import h5py
#import matplotlib.pyplot as pl

#dNch_deta=np.genfromtxt('dNch-deta.txt',delimiter='\n')
#order=[]
#for kk in range(len(dNch_deta)):
#    if(dNch_deta[kk]>0):
#       order.append(kk)
#order=np.array(order)
#print(order)
lstep =30
############# get the dNch_deta for pion,kaon,proton ##################3
pion_dN=np.genfromtxt('vdNch_deta_pion.txt',delimiter='\n')
kaon_dN=np.genfromtxt('vdNch_deta_kaon.txt',delimiter='\n')
antiproton_dN=np.genfromtxt('vdNch_deta_anti-proton.txt',delimiter='\n')
proton_dN=np.genfromtxt('vdNch_deta_proton.txt',delimiter='\n')
#### for pt distribution ####
#### for pt distribution ####
#pion
order=int(len(pion_dN)/30)
qQ=[]
for d in range(order):
    qQ.append(pion_dN[d*lstep:(d+1)*lstep])
pion_dN=np.array(qQ)
print(pion_dN.shape)
#kaon
qQ=[]
for d in range(order):
    qQ.append(kaon_dN[d*lstep:(d+1)*lstep])
kaon_dN=np.array(qQ)
#proton
qQ=[]
for d in range(order):
    qQ.append(proton_dN[d*lstep:(d+1)*lstep])
proton_dN=np.array(qQ)
#anti-proton
qQ=[]
for d in range(order):
    qQ.append(antiproton_dN[d*lstep:(d+1)*lstep])
antiproton_dN=np.array(qQ)

#print(kaon_dN.shape)
############## get the counters for differnet centrality ######
#pion
c22_4=pion_dN
c22_4=np.mean(c22_4,axis=0)
pion_dN=np.array(c22_4)

#kaon
c22_4=kaon_dN
c22_4=np.mean(c22_4,axis=0)
kaon_dN=np.array(c22_4)

#proton
c22_4=proton_dN
c22_4=np.mean(c22_4,axis=0)
proton_dN=np.array(c22_4)
#anti-proton
c22_4=antiproton_dN
c22_4=np.mean(c22_4,axis=0)
antiproton_dN=np.array(c22_4)



#########3 get the pt spectra ###########
Npart=[]
pion_dN1=[]
kaon_dN1=[]
proton_dN1=[]
antiproton_dN1=[]
for kk in range(lstep):
    Npart.append(kk*0.1+0.05)
    pion_dN1.append(pion_dN[kk]/(0.1)/(kk*0.1+0.05)/(2.0*np.pi))
    kaon_dN1.append(kaon_dN[kk]/(0.1)/(kk*0.1+0.05)/(2.0*np.pi))
    proton_dN1.append(proton_dN[kk]/(0.1)/(kk*0.1+0.05)/(2.0*np.pi))
    antiproton_dN1.append(antiproton_dN[kk]/(0.1)/(kk*0.1+0.05)/(2.0*np.pi))
Npart=np.array(Npart)
#pion
#pion_dN1=pion_dN/(0.2)
pion_dN=pion_dN1
np.savetxt('../results/pion_spectra.dat',pion_dN,fmt='%s',newline='\n')
#kaon
#kaon_dN1=kaon_dN/(0.2)
kaon_dN=kaon_dN1
np.savetxt('../results/kaon_spectra.dat',kaon_dN,fmt='%s',newline='\n')
#pion
#proton_dN1=proton_dN/(0.2)
proton_dN=proton_dN1
np.savetxt('../results/proton_spectra.dat',proton_dN,fmt='%s',newline='\n')
#proton_dN1=proton_dN/(0.2)
antiproton_dN=antiproton_dN1
np.savetxt('../results/anti-proton_spectra.dat',antiproton_dN,fmt='%s',newline='\n')

#############3 plot the results #################3333
#pionsum=np.sum(pion_dN)
#kaonsum=np.sum(kaon_dN)
#protonsum=np.sum(proton_dN)
#print(pionsum,kaonsum,protonsum)
#total_sum=pionsum+kaonsum+protonsum
#print(total_sum)
