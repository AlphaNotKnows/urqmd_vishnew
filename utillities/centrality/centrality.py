import os
import sys
import shutil
import re

root_path=sys.path[0]
result_path=root_path+"/result"
target_path=result_path+"/all_central"
result_central_dir=root_path+"/utillities/results"

# move all event into target dir
def move_all_event():
  if os.path.exists(target_path):
    shutil.rmtree(target_path)
  os.mkdir(target_path)
  event_num=0
  for cen_dir in os.listdir(result_path):
    if re.match("central",cen_dir):
      print(" enter {}".format(cen_dir))
      central_dir=result_path+"/"+cen_dir
      os.chdir(cen_dir)
      for i_event in os.listdir(central_dir):
        if re.match("event",i_event):
          shutil.move(cen_dir+"/"+i_event,target_path+"/event{}".format(event_num))
          event_num+=1
  print("event number is {}".format(event_num))
  return event_num

# move ftn2bin into target dir and transform all event
def run_ftn2bin(event_num):
  shutil.copy(result_path+"/ftn2bin",target_path)
  print("begin ftn2bin")
  output=os.popen(target_path+"/ftn2bin {}".format(event_num)).read()
  print(output)
  print("end ftn2bin")

# begin centrality sort
def central_sort():
  central=[0,3,6,10,15,20,25,30,35,40,45,50]
  shutil.copy(result_path+"/central",target_path)
  for i in range(len(central)-1):
    print("begin {} {}".format(central[i],central[i-1]))
    output=os.popen(target_path+"/central {} {}".format(central[i],central[i-1])).read()
    print(output)
    print("end {} {}".format(central[i],central[i-1]))



Event_num=move_all_event()
run_ftn2bin(Event_num)
central_sort()