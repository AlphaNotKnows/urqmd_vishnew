#!/usr/bin/env python3

import argparse
import collections
import re

import numpy as np
import h5py
#import hic.flow
#import pylab as pl

############# calculate the A ~k ~ (ARPs) part ##################3
pid=int(sys.argv[1])
M_for_ARPs=np.genfromtxt('M_for_ARPs.txt',delimiter='\n')
Qn_imag_ARPs=np.genfromtxt('Qn_imag_ARPs.txt',delimiter='\n')
Qn_real_ARPs=np.genfromtxt('Qn_real_ARPs.txt',delimiter='\n')

order = M_for_ARPs.argsort()[::-1]
# get the Qn ##
Qn=[]
for k in range(len(Qn_imag_ARPs)):
    Qn.append((complex(float(Qn_real_ARPs[k]),float(Qn_imag_ARPs[k]))))
Qn_ARPs=np.array(Qn)
# Q2,Q3,Q4
q2_ARPs=Qn_ARPs[0::3]
q3_ARPs=Qn_ARPs[1::3]
q4_ARPs=Qn_ARPs[2::3]
M_for_ARPs=M_for_ARPs[order]
#np.savetxt('M_for_ARPs_after_sorted',M_for_ARPs,fmt='%s',newline='\n')
q2_ARPs=q2_ARPs[order]
#np.savetxt('q2_ARPs_after_sorted',q2_ARPs,fmt='%s',newline='\n')
q3_ARPs=q3_ARPs[order]
#np.savetxt('q3_ARPs_after_sorted',q3_ARPs,fmt='%s',newline='\n')
q4_ARPs=q4_ARPs[order]
#np.savetxt('q4_ARPs_after_sorted',q4_ARPs,fmt='%s',newline='\n')

#MM
kM=M_for_ARPs
kM205=kM
#Q2
q2_kaon_real=q2_ARPs
k205=q2_kaon_real
#Q3
q3_kaon_real=q3_ARPs
k305=q3_kaon_real
#Q4
q4_kaon_real=q4_ARPs
k405=q4_kaon_real
############# calculate B (RPs/BPOIs) part ##################3
M_for_RPs=np.genfromtxt('M_for_RPs.txt',delimiter='\n')
Qn_imag_RPs=np.genfromtxt('Qn_imag_RPs.txt',delimiter='\n')
Qn_real_RPs=np.genfromtxt('Qn_real_RPs.txt',delimiter='\n')
# get the Qn ##
Qn=[]
for k in range(len(Qn_imag_RPs)):
    Qn.append((complex(float(Qn_real_RPs[k]),float(Qn_imag_RPs[k]))))
Qn_RPs=np.array(Qn)
# Q2,Q3,Q4
q2_RPs=Qn_RPs[0::3]
q3_RPs=Qn_RPs[1::3]
q4_RPs=Qn_RPs[2::3]

M_for_RPs=M_for_RPs[order]
#np.savetxt('M_for_RPs_after_sorted',M_for_RPs,fmt='%s',newline='\n')
q2_RPs=q2_RPs[order]
#np.savetxt('q2_RPs_after_sorted',q2_RPs,fmt='%s',newline='\n')
q3_RPs=q3_RPs[order]
#np.savetxt('q3_RPs_after_sorted',q3_RPs,fmt='%s',newline='\n')
q4_RPs=q4_RPs[order]
#np.savetxt('q4_RPs_after_sorted',q4_RPs,fmt='%s',newline='\n')

#MM
vM=M_for_RPs
vM205=vM
#Q2
q2_pion_real=q2_RPs
v205=q2_pion_real
#Q3
q3_pion_real=q3_RPs
v305=q3_pion_real
#Q4
q4_pion_real=q4_RPs
v405=q4_pion_real
# MA * MB
Msqsum05 = np.inner(vM205, kM205)  # fast sum(M^2)


###########################3 calculate the c2{2} ########################
# QA * QB*
qnsqsum205 = np.vdot(v205,k205).real# np.vdot (a,b)=a* *b


# cn{2,delta_eta =0.8}##
cn205=qnsqsum205/Msqsum05



###########################3 calculate the c3{2} ########################
# QA * QB*
qnsqsum305 = np.vdot(v305, k305).real# np.vdot (a,b)=a* *b

# cn{2,delta_eta =0.8}##
cn305=qnsqsum305/Msqsum05


###########################3 calculate the c4{2} ########################
# QA * QB*
qnsqsum405 = np.vdot(v405, k405).real# np.vdot (a,b)=a* *b

# cn{2,delta_eta =0.8}##
cn405=qnsqsum405/Msqsum05

############# calculate A POIs part ##################3

lstep=30 # lenght of the step

M_for_POIs=np.genfromtxt('M_for_vn_POIs.txt',delimiter='\n')
Qn_imag_POIs=np.genfromtxt('Qn_vn_imag_POIs.txt',delimiter='\n')
Qn_real_POIs=np.genfromtxt('Qn_vn_real_POIs.txt',delimiter='\n')
# get the Qn ##
Qn=[]
for k in range(len(Qn_imag_POIs)):
    Qn.append((complex(float(Qn_real_POIs[k]),float(Qn_imag_POIs[k]))))
Qn_POIs=np.array(Qn)
# Q2,3,4
Q2_POIs=Qn_POIs[0::3]
Q3_POIs=Qn_POIs[1::3]
Q4_POIs=Qn_POIs[2::3]
# Q2
qQ=[]
for d in order:
    qQ.append(Q2_POIs[d*lstep:(d+1)*lstep])
Q2_Pt_POIs=np.array(qQ)
#np.savetxt('Q2_Pt_POIs_after_sorted',Q2_Pt_POIs,fmt='%s',newline='\n')
# Q3
qQ=[]
for d in order:
    qQ.append(Q3_POIs[d*lstep:(d+1)*lstep])
Q3_Pt_POIs=np.array(qQ)
#np.savetxt('Q3_Pt_POIs_after_sorted',Q3_Pt_POIs,fmt='%s',newline='\n')
# Q4
qQ=[]
for d in order:
    qQ.append(Q4_POIs[d*lstep:(d+1)*lstep])
Q4_Pt_POIs=np.array(qQ)
#np.savetxt('Q4_Pt_POIs_after_sorted',Q4_Pt_POIs,fmt='%s',newline='\n')
###### dn{2} #####
# get M value for each centrality 
MMM=[]
for d in order:
    MMM.append(M_for_POIs[d*lstep:(d+1)*lstep])
pM=np.array(MMM)
#np.savetxt('M_POIs_proton_after_sorted',pM,fmt='%s',newline='\n')
pM205=pM
#Q2
q2_proton_real=Q2_Pt_POIs
p205=q2_proton_real
#Q3
q3_proton_real=Q3_Pt_POIs
p305=q3_proton_real
#Q4
q4_proton_real=Q4_Pt_POIs
p405=q4_proton_real

 # mA *MB
dm205 =(np.sum(pM205.T*vM205,axis=1)).real

########################### calculate the dA2{2｝　#################################3
# pA * QB*
dq205 =(np.sum(p205.T*v205.conjugate(),axis=1)).real# 


# d2{2}
d205=dq205/dm205

#############################3 calculate the dA3{2｝　#################################3
# pA * QB*
dq305 =(np.sum(p305.T*v305.conjugate(),axis=1)).real# 


# d3{2}
d305=dq305/dm205

#############################3 calculate the dA4{2｝　#################################3
# pA * QB*
dq405 =(np.sum(p405.T*v405.conjugate(),axis=1)).real# 

# d4{2}
d405=dq405/dm205

############# calculate B POIs part ##################3

lstep=30 # lenght of the step

M_for_BPOIs=np.genfromtxt('M_for_vn_BPOIs.txt',delimiter='\n')
Qn_imag_BPOIs=np.genfromtxt('Qn_vn_imag_BPOIs.txt',delimiter='\n')
Qn_real_BPOIs=np.genfromtxt('Qn_vn_real_BPOIs.txt',delimiter='\n')
# get the Qn ##
Qn=[]
for k in range(len(Qn_imag_BPOIs)):
    Qn.append((complex(float(Qn_real_BPOIs[k]),float(Qn_imag_BPOIs[k]))))
Qn_BPOIs=np.array(Qn)
# Q2,3,4
Q2_BPOIs=Qn_BPOIs[0::3]
Q3_BPOIs=Qn_BPOIs[1::3]
Q4_BPOIs=Qn_BPOIs[2::3]
# Q2
qQ=[]
for d in order:
    qQ.append(Q2_BPOIs[d*lstep:(d+1)*lstep])
Q2_Pt_BPOIs=np.array(qQ)
# Q3
qQ=[]
for d in order:
    qQ.append(Q3_BPOIs[d*lstep:(d+1)*lstep])
Q3_Pt_BPOIs=np.array(qQ)
# Q4
qQ=[]
for d in order:
    qQ.append(Q4_BPOIs[d*lstep:(d+1)*lstep])
Q4_Pt_BPOIs=np.array(qQ)
###### dn{2} #####
# get M value for each centrality 
MMM=[]
for d in order:
    MMM.append(M_for_BPOIs[d*lstep:(d+1)*lstep])
pM=np.array(MMM)
pBM205=pM
#Q2
q2_proton_real=Q2_Pt_BPOIs
pB205=q2_proton_real
#Q3
q3_proton_real=Q3_Pt_BPOIs
pB305=q3_proton_real
#Q4
q4_proton_real=Q4_Pt_BPOIs
pB405=q4_proton_real

 # mB *MA
dm205 =(np.sum(pBM205.T*kM205,axis=1)).real




########################### calculate the dB2{2｝　#################################3
# pB * QA*
dq205 =(np.sum(pB205.T*k205.conjugate(),axis=1)).real# 


# d2{2}
dB205=dq205/dm205

#############################3 calculate the dB3{2｝　#################################3
# pB * QA*
dq305 =(np.sum(pB305.T*k305.conjugate(),axis=1)).real# 


# d3{2}
dB305=dq305/dm205

#############################3 calculate the dB4{2｝　#################################3
# pB * QA*
dq405 =(np.sum(pB405.T*k405.conjugate(),axis=1)).real# 


# d4{2}
dB405=dq405/dm205

####################3 calculate the vn(pT) ####################################
### d2{2} ###
d205=(d205+dB205)/2

### d3{2} ###
d305=(d305+dB305)/2

### d2{2} ###
d405=(d405+dB405)/2


################## v2(pT) ##########33
v2_pT05=d205/(cn205**0.5)
np.savetxt('../results/{}_v2_pT05.dat'.format(pid),v2_pT05,fmt='%s',newline='\n')


################## v3(pT) ##########33
v3_pT05=d305/(cn305**0.5)
np.savetxt('../results/{}_v3_pT05.dat'.format(pid),v3_pT05,fmt='%s',newline='\n')



################## v4(pT) ##########33
v4_pT05=d405/(cn405**0.5)
np.savetxt('../results/{}_v4_pT05.dat'.format(pid),v4_pT05,fmt='%s',newline='\n')



