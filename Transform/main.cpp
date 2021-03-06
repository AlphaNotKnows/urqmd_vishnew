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
    std::cout<<"energy : "<<energy0<<"  energy on tau_0 : "<<momentum_sum(secondaries,0)<<" secondaries on tau_0 : "<<secondaries.size()<<std::endl;
  }

  //use all the particle on tau_0 within eta_cut to generate energy_momentum
  for(unsigned i=0;i<secondaries.size();i++){
    energy_momentum.AddParticle(secondaries[i]);
  }
  //remove over eta_cut
  if(Ex_eta_cut_mode==1){
    remove_eta_cut(secondaries,secondaries_cut,Ex_eta_cut);
  }
  else if(Ex_eta_cut_mode==0){
    double eta_cut[2]={0,0};
    if(!energy_momentum.search_eta_cut(eta_cut)){
      if(Ex_DEBUG){
        std::cout<<"no QGP generated\n";
        std::cout<<"E and p_z within eta_cut :";
      }
      std::cout<<0<<" "<<0<<std::endl;
      return 0;
    }
    remove_eta_cut(secondaries,secondaries_cut,eta_cut);
  }
  //combine to oscar1997A format
  OSCAR_19(secondaries_cut);
  //combine to urqmd ftn14 format and freestreaming to t=0
  urqmd_14(secondaries_cut);
  
  energy_momentum.CalFlow();
  WriteFlow2(energy_momentum);
  if(Ex_DEBUG){
    std::cout<<"E and p_z within eta_cut :";
  }
  std::cout<<momentum_sum(secondaries,0)<<" "<<momentum_sum(secondaries,3)<<std::endl;
}