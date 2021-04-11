#include "EPTensor.h"
namespace Transform{
  void pause(){char a;std::cout<<"press enter"<<std::endl;std::cin.get(a);}

  std::string& clear_space(std::string &str){
    if (str.empty())   
    {  
      return str;  
    }
    str.erase(0,str.find_first_not_of(" "));  
    str.erase(str.find_last_not_of(" ") + 1);  
  }
  //initialize coefficient
  double Ex_Tau_0=1.;
  double Ex_R_ver=1.;
  double Ex_R_eta=1.;
  unsigned Ex_M_bin[4]={41,101,101,101};
  double Ex_M_down[4]={0.,-10.,-10.,-10. };
  double Ex_M_up[4]={4.,10.,10.,10. };
  double Ex_Dx[4]={0.1,0.2,0.2,0.2 };
  int Ex_QGP_search_mode=1;
  double Ex_QGP_volume=1.;
  double Ex_eta_cut[2]={-0,0};
  double Ex_Edec=0.18;
  double Ex_range=3;
  double Ex_K=1.6;
  bool Ex_Vishnew=0;
  bool Ex_MUSIC=0;
  bool Ex_DEBUG=0;
  const double Pi=3.14159265358979323846264338328;
  const double HbarC=0.19733;
  std::string Ex_input_file="urqmd_result14";
  std::string Ex_output_path=".";
  std::string Ex_parameter_file="Transform_para.txt";

  void initialize(const std::string&parameter_file){
    std::ifstream parameter(parameter_file.c_str());
    std::string parameter_line;
    std::stringstream input_line;
    std::string parameter_name;
    while(!parameter.eof()){
      //clear the stream
      input_line.clear();
      parameter_line.clear();
      //prepare the input
      getline(parameter,parameter_line);
      clear_space(parameter_line);
      if(parameter_line.empty())continue;
      input_line.str(parameter_line);
      //get the name of parameter
      input_line>>parameter_name;
      if(parameter_name[0]=='/'||parameter_name[0]=='\n')continue;
      else if(parameter_name=="tau")input_line>>Ex_Tau_0;
      else if(parameter_name=="Rver")input_line>>Ex_R_ver;
      else if(parameter_name=="Reta")input_line>>Ex_R_eta;
      else if(parameter_name=="x")input_line>>Ex_M_down[1]>>Ex_M_up[1]>>Ex_M_bin[1];
      else if(parameter_name=="y")input_line>>Ex_M_down[2]>>Ex_M_up[2]>>Ex_M_bin[2];
      else if(parameter_name=="eta")input_line>>Ex_M_down[3]>>Ex_M_up[3]>>Ex_M_bin[3];
      else if(parameter_name=="t")input_line>>Ex_M_down[0]>>Ex_M_up[0]>>Ex_M_bin[0];
      else if(parameter_name=="QGP_search_mode")input_line>>Ex_QGP_search_mode;
      else if(parameter_name=="eta_cut")input_line>>Ex_eta_cut[0]>>Ex_eta_cut[1];
      else if(parameter_name=="QGP_volume")input_line>>Ex_QGP_volume;
      else if(parameter_name=="Edec")input_line>>Ex_Edec;
      else if(parameter_name=="range")input_line>>Ex_range;
      else if(parameter_name=="input")input_line>>Ex_input_file;
      else if(parameter_name=="output")input_line>>Ex_output_path;
      else if(parameter_name=="K")input_line>>Ex_K;
      else if(parameter_name=="VISHNEW")input_line>>Ex_Vishnew;
      else if(parameter_name=="MUSIC")input_line>>Ex_MUSIC;
      else if(parameter_name=="DEBUG")input_line>>Ex_DEBUG;
      else{
        if(Ex_DEBUG){
          std::cout<<parameter_name<<" is invalid parameter"<<std::endl;
        }
      }
    }
    // bin=2*(bin)+1
    for(unsigned i=0;i<4;i++){
      Ex_M_bin[i]=(2*Ex_M_bin[i])+1;
    }
    //ensure this is a path
    if(Ex_output_path.back()!='/')Ex_output_path+='/';
    for(unsigned i=0;i<4;i++){
      Ex_Dx[i]=(Ex_M_up[i]-Ex_M_down[i])/(Ex_M_bin[i]-1);
    }
  }

  void print_Ex(){
    using std::cout;
    using std::endl;
    cout<<"input file : "<<Ex_input_file<<endl;
    cout<<"output file : "<<Ex_output_path<<endl;
    cout<<"parameter file : "<<Ex_parameter_file<<endl;
    cout<<"tau_0 : "<<Ex_Tau_0<<endl;
    cout<<"R_ver : "<<Ex_R_ver<<' '<<" R_eta : "<<Ex_R_eta<<endl;;
    cout<<"x_down : "<<Ex_M_down[1]<<" x_up : "<<Ex_M_up[1]<<" x_bin : "<<Ex_M_bin[1]<<" dx : "<<Ex_Dx[1]<<endl;
    cout<<"y_down : "<<Ex_M_down[2]<<" y_up : "<<Ex_M_up[2]<<" y_bin : "<<Ex_M_bin[2]<<" dy : "<<Ex_Dx[2]<<endl;
    cout<<"eta_down : "<<Ex_M_down[3]<<" eta_up : "<<Ex_M_up[3]<<" eta_bin : "<<Ex_M_bin[3]<<" deta : "<<Ex_Dx[3]<<endl;
    cout<<"tau_down : "<<Ex_M_down[0]<<" tau_up : "<<Ex_M_up[0]<<" tau_bin : "<<Ex_M_bin[0]<<" dt : "<<Ex_Dx[0]<<endl;
    cout<<"range : "<<Ex_range<<endl;
  }

  unsigned search_bin(double x,double x_down,double x_up,unsigned bin){
    double dx=(x_up-x_down)/(bin-1);
    if(x<x_down)return 0;
    if(x>x_up)return bin-1;
    unsigned location=std::floor((x-x_down)/dx);
    return location;
  }

  const std::string get_dir(std::string path){
    int i=path.find_last_of('/');
    if(i==std::string::npos)return "./";
    else return path.erase(i+1,path.size());
  }
}
