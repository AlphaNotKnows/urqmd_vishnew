import numpy as np
import os
import shutil
import sys

central=[0,5,10,15,20,30,40,50,60,70,80]
root_path=sys.path[0]
result_dir=root_path+"/dEdeta_result"
dEdeta_exec=root_path+"/dEdeta"
if(not os.path.exists(result_dir)):
  os.mkdir(result_dir)
if(not os.path.exists(dEdeta_exec)):
  print("there is no dEdeta")
  exit()
for i in range(0,len(central)):
  if(not os.path.exists(root_path+"/central{}~{}%".format(central[i],central[i+1]))):
    print("central 0~{}".format(central[i]))
    exit()
  os.system(dEdeta_exec+" {} {}".format(central[i],central[i+1]))