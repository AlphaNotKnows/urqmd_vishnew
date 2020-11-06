import numpy as np
import os
import sys
import shutil
os.chdir(sys.path[0])
data=np.loadtxt("all_initial.txt")
data=data[(-data[:,1]).argsort(),:]
central=[0,3,6,10,15,20,25,30,35,40,45,50]
for i in range(0,len(central)-1):
  down_id=int(data.shape[0]*central[i]*0.01)
  up_id=int(data.shape[0]*central[i+1]*0.01)
  dir_path=sys.path[0]+"/central{}~{}%".format(central[i],central[i+1])
  if(os.path.exists(dir_path)):
    shutil.rmtree(dir_path)
  os.mkdir(dir_path)
  for j in range(down_id,up_id):
    os.chdir(sys.path[0])
    shutil.copy("event14_{}".format(int(data[j,0])),dir_path)
    os.chdir(dir_path)
    os.rename("event14_{}".format(int(data[j,0])),"event{}".format(int(j-down_id)))