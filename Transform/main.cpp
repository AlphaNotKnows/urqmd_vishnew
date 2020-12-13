#include "transform.h"
#include "EPTensor.h"
#include "process.h"
using namespace Transform;
using std::cout;
using std::cin;
using std::string;
using std::endl;
/**input the parameter file*/
int main(int argc,char *argv[]){
  if(argc>1){
    Ex_parameter_file.clear();
    Ex_parameter_file=std::string(argv[1]);
  }
  //initialize the parameter
  initialize(Ex_parameter_file);
  EPTensor energy_momentum;
  // print_Ex();
  std::vector<Particle> secondaries;
  search_tau(secondaries);
  // double energy0=search_energy();
  double energy_tau=0;
  for(unsigned i=0;i<secondaries.size();i++){
    energy_tau+=secondaries[i].momentum().Minkow()[0];
  }
  for(unsigned i=0;i<secondaries.size();i++){
    energy_momentum.AddParticle(secondaries[i]);
  }
  // std::cout<<"energy : "<<energy0<<"  energy on tau_0 : "<<energy_tau<<" secondaries on tau_0 : "<<secondaries.size()<<std::endl;
  energy_momentum.CalFlow();
  // write2(energy_momentum);
  WriteFlow2(energy_momentum);
}