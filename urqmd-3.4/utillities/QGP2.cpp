#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int main(){
  string input_file="urqmd_result19";
  ifstream input(input_file.c_str());
  if(!input){
    cout<<"there is no "<<input_file<<endl;
    exit(-1);
  }
  string data_line;
  stringstream input_line;
  //remove header
  for(int i=0;i<4;i++){
    data_line.clear();
    getline(input,data_line);
  }
  double QGP_energy=0,energy=0;
  int spec_num=0,secondaries=0;
  double px=0,py=0,pz=0;
  double px0=0,py0=0,pz0=0;
  while(true){
    getline(input,data_line);
    if(input.eof())break;
    input_line.clear();
    input_line.str(data_line);
    double middle,this_energy;
    int i=0;
    input_line>>middle;
    input_line>>middle;
    input_line>>middle;
    px0=abs(middle)>px0?abs(middle):px0;
    px+=middle;
    input_line>>middle;
    py0=abs(middle)>py0?abs(middle):py0;
    py+=middle;
    input_line>>middle;
    pz0=abs(middle)>pz0?abs(middle):pz0;
    pz+=middle;
    input_line>>middle;
    this_energy=middle;
    spec_num++;secondaries++;
    energy+=this_energy;
    for(i=6;i<11;i++){
      input_line>>middle;
      if(i==10&&middle!=0){
        QGP_energy+=this_energy;
        spec_num--;
      }
    }
  }
  cout<<"px_max="<<px0<<" px_bar="<<px/secondaries<<endl;
  cout<<"py_max="<<py0<<" py_bar="<<py/secondaries<<endl;
  cout<<"pz_max="<<pz0<<" pz_bar="<<pz/secondaries<<endl;
  cout<<"energy in the system is "<<energy<<endl;
  cout<<"QGP energy is "<<QGP_energy<<endl;
  cout<<"spectator number is "<<spec_num<<endl;
  cout<<"secondaries number is "<<secondaries<<endl<<endl;
}