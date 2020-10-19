import os
import shutil
import sys

root_path=sys.path[0]
# urqmd initial variable
urqmd_path=root_path+"/urqmd"
urqmd_initial_exec=urqmd_path+"/urqmd_initial.sh"
urqmd_initial_result=urqmd_path+"/urqmd_result14"
# transform variable
transform_path=root_path+"/transform"
transform_exec=transform_path+"/transform"
transform_para=transform_path+"/Transform_para.txt"
transform_input=transform_path+"/urqmd_result14"
transform_result_dir=transform_path+"/Initial"
# VISHNew variable
vishnew_path=root_path+"/VISHNew"
vishnew_exec=vishnew_path+"/VISHNew"
vishnew_input_dir=vishnew_path+"/Initial"
vishnew_result_dir=vishnew_path+"/results"
#iSS variable
iss_path=root_path+"/iSS"
iss_exec=iss_path+"/iSS"
iss_input_dir=iss_path+"/results"
iss_result=iss_path+"/OSCAR.DAT"
#osc2u variable
osc2u_path=root_path+"/osc2u"
osc2u_exec=osc2u_path+"/osc2u"
osc2u_input=osc2u_path+"/OSCAR.DAT"
osc2u_result=osc2u_path+"/fort.14"
osc2u_result_move=osc2u_path+"/frez_start"
#urqmd frezout
urqmd_frez_input=urqmd_path+"/frez_start"
urqmd_frez_exec=urqmd_path+"/urqmd_frez.sh"
urqmd_frez_result=urqmd_path+"/frez_result"
# result dir
result_path=root_path+"/result"
result_file=result_path+"/event"


def run_urqmd_initial():
  print("begin urqmd initial")
  os.chdir(urqmd_path)
  os.system(urqmd_initial_exec)
  if(os.path.exists(transform_input)):
    os.remove(transform_input)
  shutil.move(urqmd_initial_result,transform_input)
  print("end urqmd initial")


def run_transform():
  print("begin transform")
  os.chdir(transform_path)
  if(not os.path.exists(transform_result_dir)):
    os.mkdir(transform_result_dir)
  os.system(transform_exec+' '+transform_para)
  if(os.path.exists(vishnew_input_dir)):
    shutil.rmtree(vishnew_input_dir)
  shutil.move(transform_result_dir,vishnew_input_dir)
  print("end transform")

def run_vishnew():
  print("begin vishnew")
  os.chdir(vishnew_path)
  if(not os.path.exists(vishnew_result_dir)):
    os.mkdir(vishnew_result_dir)
  os.system(vishnew_exec)
  if(os.path.exists(iss_input_dir)):
    shutil.rmtree(iss_input_dir)
  shutil.move(vishnew_result_dir,iss_input_dir)
  print("end vishnew")

def run_iSS():
  print("begin iSS")
  os.chdir(iss_path)
  os.system(iss_exec)
  if(os.path.exists(osc2u_input)):
    os.remove(osc2u_input)
  shutil.move(iss_result,osc2u_input)
  print("end iSS")


def run_osc2u():
  print("begin osc2u")
  os.chdir(osc2u_path)
  os.system(osc2u_exec+"<"+osc2u_input)
  os.rename(osc2u_result,osc2u_result_move)
  if(os.path.exists(urqmd_frez_input)):
    os.remove(urqmd_frez_input)
  shutil.move(osc2u_result_move,urqmd_frez_input)
  print("end osc2u")

def run_urqmd_frez():
  print("begin urqmd frezout")
  os.chdir(urqmd_path)
  os.system(urqmd_frez_exec)
  print("end urqmd frezout")



# main process
for i in range(0,1):
  run_urqmd_initial()
  run_transform()
  run_vishnew()
  run_iSS()
  run_osc2u()
  run_urqmd_frez()
  if(not os.path.exists(result_path)):
    os.mkdir(result_path)
  
  shutil.move(urqmd_frez_result,result_file+str(i))