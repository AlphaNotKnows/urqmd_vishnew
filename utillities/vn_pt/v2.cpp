#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<complex.h>
#include<math.h>
using namespace std;
int main(int argc,char*argv[]){
  int n=2;
  if(argc>1){
    n=stoi(argv[1]);
  }
  const std::string file_path="../result/particle.dat";
  ifstream input(file_path.c_str());
  const string output_file="../result/v2_pt.txt";
  cout<<"the v"<<2<<" is wrote to file "<<output_file<<endl;
  int event_num=0;
  while(true){
    int secondaries_num=0;
    input.read((char*)&secondaries_num,sizeof(int));
    //judge the end of the file
    if(input.tellg()==-1)break;
    event_num+=1;
    complex<double> Qn,Q2n;
    const complex<double> j(0,1);
    for(int i=0;i<secondaries_num;i++){
      int pid,charge,iso3;
      double mass,p_T,phi,rapid;
      //read data of a particle
      input.read((char*)&pid,sizeof(pid));
      input.read((char*)&iso3,sizeof(iso3));
      input.read((char*)&charge,sizeof(charge));
      input.read((char*)&mass,sizeof(mass));
      input.read((char*)&p_T,sizeof(p_T));
      input.read((char*)&phi,sizeof(phi));
      input.read((char*)&rapid,sizeof(rapid));
      //vn search
      if(charge!=0){
        Qn+=exp(complex<double>(0,n*phi));
        Q2n+=exp(complex<double>(0,2*n*phi));
      }
      
    }
  }
}