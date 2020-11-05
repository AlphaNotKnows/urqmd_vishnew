#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int main(int argc,char*argv[]){
  string input_file="urqmd_result19";
  if(argc>1)input_file=string(argv[1]);
  ifstream input(input_file.c_str());
  string data_line;
  stringstream input_line;
  //remove header
  for(int i=0;i<4;i++){
    data_line.clear();
    getline(input,data_line);
  }
  double QGP_energy=0,energy=0;
  int spec_num=0;
  while(true){
    getline(input,data_line);
    if(input.eof())break;
    input_line.clear();
    input_line.str(data_line);
    double middle,this_energy;
    for(int i=0;i<11;i++){
      input_line>>middle;
      if(i==5){
        this_energy=middle;
        spec_num++;
        energy+=this_energy;
      }
      else if(i==10&&middle!=0){
        QGP_energy+=this_energy;
        spec_num--;
      }
    }
  }
  cout<<"energy in the system is "<<energy<<endl;
  cout<<"QGP energy is "<<QGP_energy<<endl;
  cout<<"spectator number is "<<spec_num<<endl;
}