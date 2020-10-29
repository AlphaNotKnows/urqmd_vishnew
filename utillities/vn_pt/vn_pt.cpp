#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
using namespace std;
int main(int argc,char*argv[]){
  int n=2;
  if(argc>1){
    n=stoi(argv[1]);
  }
  ifstream input("../particle.dat");
  string output_file="../v";
  output_file+=to_string(n);
  output_file+="_pt.txt";
  cout<<"the v"<<n<<" is wrote to file "<<output_file<<endl;
  while(true){
    int secondaries_num=0;
    input.read((char*)&secondaries_num,sizeof(int));
    if(input.tellg()==-1)break;
    for(int i=0;i<secondaries_num;i++){
      int pid,charge;
      double mass,p_T,phi,rapid;
      input.read((char*)&pid,sizeof(pid));
      input.read((char*)&charge,sizeof(charge));
      input.read((char*)&mass,sizeof(mass));
      input.read((char*)&p_T,sizeof(p_T));
      input.read((char*)&phi,sizeof(phi));
      input.read((char*)&rapid,sizeof(rapid));
      if(charge!=0&&rapid>0&&rapid<2&&p_T>0.2&&p_T<5){
        
      }
    }
  }
}