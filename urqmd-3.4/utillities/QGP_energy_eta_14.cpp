#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
using namespace std;
int main(int argc,char*argv[]){
  string input_file="urqmd_QGP_14.txt";
  if(argc>1){
    input_file=string(argv[1]);
  }
  const string output_file=input_file+"_result.txt";
  ifstream input(input_file.c_str());
  ofstream output(output_file.c_str());
  if(!input){
    cerr<<input_file<<" is not exist\n";
    exit(-1);
  }
   if(!output){
    cerr<<output_file<<" can't be open\n";
    exit(-1);
  }

  string data_line;
  stringstream input_line;
  while(getline(input,data_line)){
    if(input.eof()){
      return 0;
    }
    for(int i=0;i<16;i++){
      data_line.clear();
      getline(input,data_line);
    }
    data_line.clear();
    getline(input,data_line);
    input_line.str(data_line);
    int secondaries_num=0;
    input_line>>secondaries_num;
    // remove collision line
    input_line.clear();
    data_line.clear();
    getline(input,data_line);
    data_line.clear();
    input_line.clear();

    double middle=0;
    double p_sum[4]={0};
    double energy_low=0;
    double energy_high=0;
    for(int i=0;i<secondaries_num;i++){
      getline(input,data_line);
      input_line.str(data_line);
      double p[4]={0,0,0,0};
      double x[4]={0,0,0,0};
      // input_line>>middle>>middle>>middle>>middle>>p[0]>>p[1]>>p[2]>>p[3];
      for(int j=0;j<4;j++){
        input_line>>x[j];
      }
      double eta=0.5*log((x[0]+x[3])/(x[0]-x[3]));
      // input_line>>p[0]>>p[1]>>p[2]>>p[3];
      for(int j=0;j<4;j++){
        input_line>>p[j];
      }
      for(int j=0;j<4;j++){
        p_sum[j]+=p[j];
      }
      data_line.clear();
      input_line.clear();
      if(abs(eta)>2.){
        energy_high+=p[0];
      }
      else energy_low+=p[0];
    }
    // output<<secondaries_num<<' '<<p_sum[0]<<' '<<p_sum[1]<<' '<<p_sum[2]<<' '<<p_sum[3]<<endl;
    output<<energy_low<<' '<<energy_high<<endl;
  }
}