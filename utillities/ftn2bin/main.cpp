#include "Vector4.h"
#include "Particle.h"
#include "process.h"
using Transform::remove_header;
using Transform::get_secondaries;
using Transform::Particle;
using Transform::write_event;
int main(int argc,char*argv[]){
  // input the number of event to count
  int event_num=1;
  if(argc>1){
    event_num=std::stoi(argv[1]);
  }
  write_event(event_num);
}