#include "transform.h"
#include "EPTensor.h"
#include "process.h"
using namespace Transform;
using std::cout;
using std::cin;
using std::string;
using std::endl;
EPTensor energy_momentum;
/**input the parameter file*/
int main(int argc,char *argv[]){
  if(argc>1){
    Ex_parameter_file.clear();
    Ex_parameter_file=std::string(argv[1]);
  }
  //initialize the parameter
  initialize(Ex_parameter_file);
  std::vector<Particle> secondaries;
  search_tau(secondaries);
  search_spectator(secondaries);
  for(unsigned i=0;i<secondaries.size();i++){
    energy_momentum.AddParticle(secondaries[i]);
  }
  energy_momentum.CalFlow();
  WriteFlow2(energy_momentum);
  write2(energy_momentum);
}