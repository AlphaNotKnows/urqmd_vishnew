#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
//eta bin
const double deta=0.5;
//eta range
const double eta_range=6;
//bin number
const int bin_num=std::round(eta_range/deta)*2+1;
//dNdeta array
std::vector<double> dNdeta_all(bin_num,0);
std::vector<double> dNdeta_p_pos(bin_num,0);
std::vector<double> dNdeta_p_neg(bin_num,0);
std::vector<double> dNdeta_pi_pos(bin_num,0);
std::vector<double> dNdeta_pi_neg(bin_num,0);
std::vector<double> dNdeta_K_pos(bin_num,0);
std::vector<double> dNdeta_K_neg(bin_num,0);
int main(int argc,char*argv[]){
  std::string file_path;
  int central_min=0,central_max=100;
  if(argc>2){
    central_min=std::stoi(argv[1]);
    central_max=std::stoi(argv[2]);
  }
  file_path="../results/particle";
  file_path+=to_string(central_min);
  file_path+="~";
  file_path+=to_string(central_max);
  file_path+="%.dat";
  ifstream input(file_path.c_str());
  string output_file="../results/dNdeta";
  output_file+=to_string(central_min);
  output_file+="~";
  output_file+=to_string(central_max);
  output_file+="%.txt";
  cout<<"write to file "<<output_file<<endl;
  ofstream output(output_file.c_str());
  int event_num=0;
  while(true){
    int secondaries_num=0;
    input.read((char*)&secondaries_num,sizeof(int));
    //judge the end of the file
    if(input.tellg()==-1)break;
    event_num++;
    std::vector<int> dNdeta_all_this(bin_num,0);
    std::vector<double> dNdeta_p_pos_this(bin_num,0);
    std::vector<double> dNdeta_p_neg_this(bin_num,0);
    std::vector<double> dNdeta_pi_pos_this(bin_num,0);
    std::vector<double> dNdeta_pi_neg_this(bin_num,0);
    std::vector<double> dNdeta_K_pos_this(bin_num,0);
    std::vector<double> dNdeta_K_neg_this(bin_num,0);
    for(int i=0;i<secondaries_num;i++){
      int pid,charge,iso3;
      double mass,p_T,phi,eta;
      //read data of a particle
      input.read((char*)&pid,sizeof(pid));
      input.read((char*)&iso3,sizeof(iso3));
      input.read((char*)&charge,sizeof(charge));
      input.read((char*)&mass,sizeof(mass));
      input.read((char*)&p_T,sizeof(p_T));
      input.read((char*)&phi,sizeof(phi));
      input.read((char*)&eta,sizeof(eta));
      int bin_id=std::floor((eta+eta_range)/deta);
      //count all Nch
      if(charge!=0){
        //get eta bin
        dNdeta_all_this[bin_id]++;
      }
      //count p+-
      if(pid>=1&&pid<=16&&iso3==1){
        dNdeta_p_pos_this[bin_id]++;
      }
      else if((-pid)>=1&&(-pid)<=16&&(-iso3)==1){
        dNdeta_p_neg_this[bin_id]++;
      }
      //count pi+-
      else if(pid==101&&charge>0){
        dNdeta_pi_pos_this[bin_id]++;
      }
      else if(pid==101&&charge<0){
        dNdeta_pi_neg_this[bin_id]++;
      }
      // count K+-
      else if(pid==106){
        dNdeta_K_pos_this[bin_id]++;
      }
      else if(pid==-106){
        dNdeta_K_neg_this[bin_id]++;
      }
    }
    for(int i=0;i<bin_num;i++){
      dNdeta_all[i]+=dNdeta_all_this[i]/deta;
      dNdeta_p_pos[i]+=dNdeta_p_pos_this[i]/deta;
      dNdeta_p_neg[i]+=dNdeta_p_neg_this[i]/deta;
      dNdeta_pi_pos[i]+=dNdeta_pi_pos_this[i]/deta;
      dNdeta_pi_neg[i]+=dNdeta_pi_neg_this[i]/deta;
      dNdeta_K_pos[i]+=dNdeta_K_pos_this[i]/deta;
      dNdeta_K_neg[i]+=dNdeta_K_neg_this[i]/deta;
    }
  }
  for(int i=0;i<bin_num;i++){
    dNdeta_all[i]/=event_num;
    dNdeta_p_pos[i]/=event_num;
    dNdeta_p_neg[i]/=event_num;
    dNdeta_pi_pos[i]/=event_num;
    dNdeta_pi_neg[i]/=event_num;
    dNdeta_K_pos[i]/=event_num;
    dNdeta_K_neg[i]/=event_num;
    //get eta number
    double eta_num=i*deta-eta_range;
    output<<setw(4)<<eta_num<<' '<<setw(6)<<dNdeta_all[i]<<' '<<dNdeta_p_pos[i]<<' '<<dNdeta_p_neg[i]<<' '<<dNdeta_pi_pos[i]<<' '<<dNdeta_pi_neg[i]<<' '<<dNdeta_K_pos[i]<<' '<<dNdeta_K_neg[i]<<endl;
  }
}