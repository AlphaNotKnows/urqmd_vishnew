#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int main(int argc,char*argv[]){
  string input_file="urqmd_QGP_19.txt";
  string output_file="QGP_result_energy_19.txt";
  if(argc>1){
    input_file=string(argv[1]);
  }
  ifstream input(input_file.c_str());
  ofstream output(output_file.c_str());
  if(!input){
    cerr<<input_file<<" is not exist\n";
    exit(-1);
  }

  string data_line;
  stringstream input_line;
  int event_num=0;
  while(getline(input,data_line)){
    if(input.eof())break;
    for(int i=0;i<2;i++){
      getline(input,data_line);
    }
    event_num++;
    int secondaries_num=0;
    int middle=0;
    data_line.clear();
    getline(input,data_line);
    input_line.str(data_line.c_str());
    input_line>>middle>>secondaries_num;
    double p_sum[4]={0};
    for(int j=0;j<secondaries_num;j++){
      getline(input,data_line);
      input_line.str(data_line);
      double p[4]={0};
      double pdg=0;
      double counter=0;
      double mass=0;
      //frezout position
      double x[4]={0};
      //particle counter
      input_line>>counter;
      //pdg id
      input_line>>pdg;
      //momentum
      input_line>>p[1]>>p[2]>>p[3]>>p[0];
      for(int k=0;k<4;k++){
        p_sum[k]+=p[k];
      }
    }
    output<<secondaries_num<<' '<<p_sum[0]<<' '<<p_sum[1]<<' '<<p_sum[2]<<' '<<p_sum[3]<<endl;
  }
  input.close();
  output.close();
}