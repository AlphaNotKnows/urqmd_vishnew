import os
import shutil
import sys
import numpy as np

root_path=sys.path[0]
# urqmd initial variable
urqmd_path=root_path+"/urqmd"
urqmd_initial_exec=urqmd_path+"/urqmd_initial.sh"
urqmd_initial_result=urqmd_path+"/urqmd_result14"
initial_path=root_path+"/Initial"
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

def run_urqmd_initial(event_num):
  # run urqmd initial
  print("begin {} urqmd initial".format(event_num))
  urqmd_initial_path=urqmd_path+"/Initial"
  urqmd_exec=urqmd_path+"/urqmd_initial.sh"
  urqmd_result14=urqmd_path+"/urqmd_result14"
  urqmd_result19=urqmd_path+"/urqmd_result19"
  if(os.path.exists(urqmd_initial_path)):
    shutil.rmtree(urqmd_initial_path)
  os.mkdir(urqmd_initial_path)
  os.chdir(urqmd_path)
  for i in range(0,event_num):
    output_str=os.popen(urqmd_exec).read()
    print(output_str)
    shutil.move(urqmd_result14,urqmd_initial_path+"/event14_{}".format(i))
    shutil.move(urqmd_result19,urqmd_initial_path+"/event19_{}".format(i))
  # get urqmd energy
  print("begin QGP energy")
  output_str=os.popen(urqmd_path+"/QGP_energy "+str(event_num)).read()
  os.chdir(urqmd_initial_path)
  print("end QGP energy")
  print("begin centrality sort")
  data=np.loadtxt(urqmd_initial_path+"/all_initial.txt")
  data=data[(-data[:,1]).argsort(),:]
  #sort as central
  central=[0,3,6,10,15,20,25,30,35,40,45,50]
  central_path=urqmd_initial_path+"/central"
  if(os.path.exists(central_path)):
    shutil.rmtree(central_path)
  os.mkdir(central_path)
  for i in range(0,len(central)-1):
    down_id=int(data.shape[0]*central[i]*0.01)
    up_id=int(data.shape[0]*central[i+1]*0.01)
    dir_path=central_path+"/central{}~{}%".format(central[i],central[i+1])
    if(os.path.exists(dir_path)):
      shutil.rmtree(dir_path)
    os.mkdir(dir_path)
    for j in range(down_id,up_id):
      os.chdir(sys.path[0])
      shutil.copy(urqmd_initial_path+"/event14_{}".format(int(data[j,0])),dir_path)
      os.chdir(dir_path)
      os.rename(dir_path+"/event14_{}".format(int(data[j,0])),"event{}".format(int(j-down_id)))
  if(os.path.exists(initial_path)):
    shutil.rmtree(initial_path)
  shutil.move(central_path,initial_path)
  print("end centrality sort")
  

# def run_urqmd_initial():
#   print("begin urqmd initial")
#   os.chdir(urqmd_path)
#   output_str=os.popen(urqmd_initial_exec)
#   if(os.path.exists(transform_input)):
#     os.remove(transform_input)
#   shutil.move(urqmd_initial_result,transform_input)
#   print("end urqmd initial")


def run_transform():
  print("begin transform")
  os.chdir(transform_path)
  if(not os.path.exists(transform_result_dir)):
    os.mkdir(transform_result_dir)
  output_str=os.popen(transform_exec+' '+transform_para).read()
  print(output_str)
  if(os.path.exists(vishnew_input_dir)):
    shutil.rmtree(vishnew_input_dir)
  shutil.move(transform_result_dir,vishnew_input_dir)
  print("end transform")

def run_vishnew():
  print("begin vishnew")
  os.chdir(vishnew_path)
  if(not os.path.exists(vishnew_result_dir)):
    os.mkdir(vishnew_result_dir)
  output_str=os.popen(vishnew_exec).read()
  print(output_str)
  if(os.path.exists(iss_input_dir)):
    shutil.rmtree(iss_input_dir)
  shutil.move(vishnew_result_dir,iss_input_dir)
  print("end vishnew")

def run_iSS():
  print("begin iSS")
  os.chdir(iss_path)
  output_str=os.popen(iss_exec).read()
  print(output_str)
  if(os.path.exists(osc2u_input)):
    os.remove(osc2u_input)
  shutil.move(iss_result,osc2u_input)
  print("end iSS")


def run_osc2u():
  print("begin osc2u")
  os.chdir(osc2u_path)
  output_str=os.popen(osc2u_exec+"<"+osc2u_input).read()
  print(output_str)
  os.rename(osc2u_result,osc2u_result_move)
  if(os.path.exists(urqmd_frez_input)):
    os.remove(urqmd_frez_input)
  shutil.move(osc2u_result_move,urqmd_frez_input)
  print("end osc2u")

def run_urqmd_frez():
  print("begin urqmd frezout")
  os.chdir(urqmd_path)
  output_str=os.popen(urqmd_frez_exec).read()
  print(output_str)
  print("end urqmd frezout")



# main process
event_num=10
run_urqmd_initial(event_num)
for central_dir in os.listdir(initial_path):
  if(central_dir.find("central")==-1):
    continue
  print("enter "+initial_path+'/'+central_dir)
  for initial_file in os.listdir(initial_path+'/'+central_dir):
    os.chdir(initial_path+'/'+central_dir)
    if(initial_file.find("event")==-1):
      continue
    print("initial with :"+initial_file)
    shutil.copy(initial_path+'/'+central_dir+'/'+initial_file,transform_input)
    # run_urqmd_initial()
    run_transform()
    run_vishnew()
    run_iSS()
    run_osc2u()
    run_urqmd_frez()
    if(not os.path.exists(result_path)):
      os.mkdir(result_path)
    target_dir=result_path+'/'+central_dir
    if(not os.path.exists(target_dir)):
      os.mkdir(target_dir)
    shutil.move(urqmd_frez_result,target_dir)
    os.rename(target_dir+'/frez_result',target_dir+"/"+initial_file)