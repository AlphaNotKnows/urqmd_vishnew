import sys
import os
import shutil
import re
root_path=sys.path[0]
result_path=root_path+"/result"
ftn2bin_path=root_path+"/utillities/results"
dNdeta_path=root_path+"/utillities/dNdy"
central=[0,3,6,10,15,20,25,30,35,40,45,50]
# loop over all directory
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