#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
  ifstream input("../all_events.dat");
  if(!input){
    cout<<"there is no all_events.dat file"<<endl;
    exit(-1);
  }
  int event_num=0;
  while(true){
    int secondaries_num=0;
    input.read((char*)&secondaries_num,sizeof(int));
    //judge the end of the file
    if(input.tellg()==-1)break;
    string output_file="../Outputbyevent/particle_Event";
    output_file+=to_string(event_num);
    event_num++;
    output_file+=".txt";
    ofstream output(output_file.c_str());
    if(!output){
      cout<<"there is no dir Outputbyevent\n";
      exit(-1);
    }
    for(int i=0;i<secondaries_num;i++){
      int pid,charge,iso3;
      double mass,pT,phi,eta;
      //read data of a particle
      input.read((char*)&pid,sizeof(pid));
      input.read((char*)&iso3,sizeof(iso3));
      input.read((char*)&charge,sizeof(charge));
      input.read((char*)&mass,sizeof(mass));
      input.read((char*)&pT,sizeof(pT));
      input.read((char*)&phi,sizeof(phi));
      input.read((char*)&eta,sizeof(eta));
      output<<pid<<' '<<charge<<' '<<iso3<<' '<<pT<<' '<<phi<<' '<<eta<<endl;
    }
    output.close();
  }
  ofstream output("../EVENTS_HEADFILE.dat");
  output<<event_num;
  output.close();
}