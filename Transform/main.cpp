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
  if(Ex_DEBUG){
    print_Ex();
  }
  //secondaries is the vector to store all on tau_0, secondaries_cut store all particles exceed eta_cut
  std::vector<Particle> secondaries,secondaries_cut;
  search_tau(secondaries);
  if(Ex_DEBUG){
    double energy0=search_energy();
    double energy_tau=0;
    for(unsigned i=0;i<secondaries.size();i++){
      energy_tau+=secondaries[i].momentum().Minkow()[0];
    }
    std::cout<<"energy : "<<energy0<<"  energy on tau_0 : "<<energy_tau<<" secondaries on tau_0 : "<<secondaries.size()<<std::endl;
  }

  //remove over eta_cut
  remove_eta_cut(secondaries,secondaries_cut);
  //combine to oscar1997A format
  OSCAR_19(secondaries_cut);
  
  //use all the particle on tau_0 within eta_cut to generate energy_momentum
  for(unsigned i=0;i<secondaries.size();i++){
    energy_momentum.AddParticle(secondaries[i]);
  }
  energy_momentum.CalFlow();
  WriteFlow2(energy_momentum);
}