#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<cmath>
using namespace std;
//eta bin
const double deta=0.5;
//eta range
const double eta_range=7;
//bin number
const int bin_num=std::round(eta_range/deta)*2+1;

vector<double>dEdeta(bin_num,0);


int main(int argc,char*argv[]){
  int central_low=0;
  int central_high=0;
  if(argc>=3){
    central_low=stoi(argv[1]);
    central_high=stoi(argv[2]);
  }
  else
  {
    cerr<<" the argument is not enough\n";
    exit(-1);
  }
  char output_file[200];
  sprintf(output_file,"dEdeta_result/dEdeta%d~%d%%.txt",central_low,central_high);
  ofstream output(output_file);
  if(!output){
    cerr<<"there is no dEdeta directory\n";
    exit(-1);
  }
  int initial_num=0;
  int event_num=0;


  while(true)
  {
    //event file name
    char input_file[200];
    sprintf(input_file,"./central%d~%d%%/event%d",central_low,central_high,initial_num);
    ifstream input(input_file);
    initial_num++;
    if(!input){
      cout<<"initial number "<<initial_num-1<<endl;
      break;
    }

    //begin loop
    string data_line;
    stringstream input_line;
    //loop over sample
    int sample_num=0;
    while(getline(input,data_line)){
      if(input.eof()){
        return 0;
      }
      //begin a new sample
      sample_num++;
      //remove header
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
      //loop over secondaries
      for(int i=0;i<secondaries_num;i++){
        getline(input,data_line);
        input_line.str(data_line);
        double x[4]={0};
        double p[4]={0,0,0,0};
        for(int j=0;j<4;j++){
          input_line>>x[j];
        }
        for(int j=0;j<4;j++){
          input_line>>p[j];
        }
        data_line.clear();
        input_line.clear();
        //count dEdeta
        const double eta=0.5*log((x[0]+x[3])/(x[0]-x[3]));
        const int bin_id=std::floor((eta+eta_range)/deta);
        if(bin_id>=bin_num)continue;
        dEdeta[bin_id]+=p[0]/deta;
      }
    }
    event_num+=sample_num;
    input.close();
  }
  double energy=0;
  for(int i=0;i<bin_num;i++){
    dEdeta[i]/=event_num;
    double eta=i*deta-eta_range;
    output<<eta<<' '<<dEdeta[i]<<endl;
    energy+=dEdeta[i]*deta;
  }
  cout<<"event number = "<<event_num<<endl;
  cout<<"energy = "<<energy<<endl;
  output.close();
}