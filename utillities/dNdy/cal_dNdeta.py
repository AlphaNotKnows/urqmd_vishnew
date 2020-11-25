import sys
import os
import shutil
import re
import numpy as np
root_path=sys.path[0]
result_path=root_path+"/result"
ftn2bin_path=root_path+"/utillities/results"
dNdeta_path=root_path+"/utillities/dNdy"
# loop over all directory
central=[0,5,10,15,20,30,40,50,60,70]
def cal_dNdeta():
  for i in range(len(central)-1):
    central_dir=result_path+"/central{}~{}%".format(central[i],central[i+1])
    if(not os.path.exists(central_dir)):
      continue
    print("begin central{}~{}%".format(central[i],central[i+1]))
    shutil.copy(result_path+"/ftn2bin",central_dir)
    os.chdir(central_dir)
    event_num=0
    # get the number of event have been calculated
    for i_file in os.listdir(central_dir):
      if re.match("event",i_file):
        event_num+=1
    print(" event number : {}".format(event_num))
    os.system(central_dir+"/ftn2bin {}".format(event_num))
    shutil.move(central_dir+"/all_events.dat",ftn2bin_path+"/particle{}~{}%.dat".format(central[i],central[i+1]))
    os.chdir(dNdeta_path)
    os.system(dNdeta_path+"/dNdeta {} {}".format(central[i],central[i+1]))
    print("end central{}~{}%".format(central[i],central[i+1]))

def cal_dNdeta01():
  os.chdir(ftn2bin_path)
  dNdeta0=np.arange((len(central)-1)*8).reshape(len(central)-1,8)
  for i in range(len(central)-1):
    os.chdir(dNdeta_path)
    os.system(dNdeta_path+"/dNdeta {} {}".format(central[i],central[i+1]))
    os.chdir(ftn2bin_path)
    dNdeta=np.loadtxt(ftn2bin_path+"/dNdeta{}~{}%.txt".format(central[i],central[i+1]))
    dNdeta0[i][0]=(central[i]+central[i+1])/2
    for j in range(1,8):
      dNdeta0[i][j]=dNdeta[(dNdeta.shape[0]-1)/2][j]
      
  np.savetxt(ftn2bin_path+"/dNdeta0.txt",dNdeta0)

def cal_dNdeta0():
  os.chdir(ftn2bin_path)
  dNdeta0=np.arange((len(central)-1)*8).reshape(len(central)-1,8)
  for i in range(len(central)-1):
    dNdeta=np.loadtxt(ftn2bin_path+"/dNdeta{}~{}%.txt".format(central[i],central[i+1]))
    dNdeta0[i][0]=(central[i]+central[i+1])/2
    for j in range(1,8):
      dNdeta0[i][j]=dNdeta[(dNdeta.shape[0]-1)/2][j]
      
  np.savetxt(ftn2bin_path+"/dNdeta0.txt",dNdeta0)

cal_dNdeta()
cal_dNdeta0()