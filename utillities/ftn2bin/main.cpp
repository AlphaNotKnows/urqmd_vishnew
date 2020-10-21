#include "Vector4.h"
#include "Particle.h"
#include "process.h"
#include "Vector4.cpp"
#include "Particle.cpp"
#include "process.cpp"
using namespace std;
using Transform::remove_header;
using Transform::get_secondaries;
using Transform::Particle;
int main(int argc,char*argv[]){
  // input the number of event to count
  int event_num=0;
  if(argc>1){
    event_num=stoi(argv[1]);
  }
  for(int event_id=0;event_id<event_num;event_id++){
    string input_file="event";
    input_file+=to_string(event_id);
    ifstream input(input_file);
    ofstream output(input_file+"_bin.dat");
    vector<Particle>secondaries;
    while(get_secondaries(input,secondaries)){
      output<<secondaries.size()<<endl;
      secondaries.clear();
    }
  }
}