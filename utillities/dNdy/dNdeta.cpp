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
    std::vector<int> dNdeta(bin_num,0);
    for(int i=0;i<secondaries_num;i++){
      int pid,charge;
      double mass,p_T,phi,eta;
      //read data of a particle
      input.read((char*)&pid,sizeof(pid));
      input.read((char*)&charge,sizeof(charge));
      input.read((char*)&mass,sizeof(mass));
      input.read((char*)&p_T,sizeof(p_T));
      input.read((char*)&phi,sizeof(phi));
      input.read((char*)&eta,sizeof(eta));
      //count all Nch
      if(charge!=0){
        //get eta bin
        int bin_id=std::floor((eta+eta_range)/deta);
        dNdeta[bin_id]++;
      }
    }
    for(int i=0;i<bin_num;i++){
      dNdeta_all[i]+=dNdeta[i]/deta;
    }
  }
  for(int i=0;i<bin_num;i++){
    dNdeta_all[i]/=event_num;
    //get eta number
    double eta_num=i*deta-eta_range;
    output<<setw(4)<<eta_num<<' '<<setw(6)<<dNdeta_all[i]<<endl;
  }
}