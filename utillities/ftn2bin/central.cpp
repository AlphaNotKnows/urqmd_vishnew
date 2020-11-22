#include "Vector4.h"
#include "Particle.h"
#include "process.h"
#include<ctime>
// #include "Vector4.cpp"
// #include "Particle.cpp"
// #include "process.cpp"
using Transform::remove_header;
using Transform::get_secondaries;
using Transform::Particle;
using Transform::write_event;
int main(int argc,char*argv[]){
  // input the number of event to count
  int central_min=0,central_max=100;
  if(argc>=3){
    central_min=std::stoi(argv[1]);
    central_max=std::stoi(argv[2]);
  }
  Transform::search_central(Transform::all_event_file,double(central_min)/100,double(central_max)/100);
}