import os
import sys
import shutil
def urqmd_initial(event_num):
  urqmd_path=sys.path[0]+"/.."
  urqmd_result_path=urqmd_path+"result"
  urqmd_exec=urqmd_path+"/urqmd_initial.sh"
  urqmd_result14=urqmd_path+"/urqmd_result14"
  urqmd_result19=urqmd_path+"/urqmd_result19"
  if(not os.path.exists(urqmd_result_path)):
    os.mkdir(urqmd_result_path)
  os.chdir(urqmd_path)
  for i in range(0,event_num):
    os.system(urqmd_exec)
    shutil.move(urqmd_result14,urqmd_result_path+"/event14_{}".format(i))
    shutil.move(urqmd_result19,urqmd_result_path+"/event19_{}".format(i))
