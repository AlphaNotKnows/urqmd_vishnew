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
    // for(int i=0;i<secondaries.size();i++){
    //   if(std::abs(secondaries[i].space().Milne()[0]-Ex_Tau_0)>0.0001*Ex_Dx[0]){
    //     // std::cout<<secondaries[i];
    //     std::cout<<i<<':'<<cross_surface(secondaries[i],-1)<<std::endl;
    //   }
    // }
    double energy0=search_energy();
    std::cout<<"energy : "<<energy0<<"  energy on tau_0 : "<<momentum_sum(secondaries,0)<<" secondaries on tau_0 : "<<secondaries.size()<<std::endl;
  }

  //use all the particle on tau_0 within eta_cut to generate energy_momentum
  for(unsigned i=0;i<secondaries.size();i++){
    energy_momentum.AddParticle(secondaries[i]);
  }

  //check momentum in EPTensor
  if(Ex_DEBUG){
    std::cout<<"p[0,1,2,3] in EPTensor : ";
    for(int i=0;i<4;i++){
      std::cout<<energy_momentum.momentum(i)<<' ';
    }
    std::cout<<std::endl;
    std::cout<<"p[0,1,2,3] for EPTensor : ";
    for(int i=0;i<4;i++){
      std::cout<<momentum_Milne_sum(secondaries,i)<<' ';
    }
    std::cout<<std::endl;
  }
  energy_momentum.CalFlow();
  //do QGP judge
  if(Ex_QGP_search_mode==1){
    if(Ex_DEBUG){
      std::cout<<"QGP judge with input eta cut\n";
    }
    remove_eta_cut(secondaries,secondaries_cut,Ex_eta_cut);
  }
  else if(Ex_QGP_search_mode==0){
    if(Ex_DEBUG){
      std::cout<<"QGP judge with searched eta cut\n";
    }
    double eta_cut[2]={0,0};
    if(!energy_momentum.search_eta_cut(eta_cut)){
      if(Ex_DEBUG){
        std::cout<<"no QGP generated\n";
        std::cout<<"E and p_z within eta_cut :";
      }
      std::cout<<eta_cut[0]<<" "<<eta_cut[1]<<" "<<0<<" "<<0<<std::endl;
      return 0;
    }
    remove_eta_cut(secondaries,secondaries_cut,eta_cut);
  }
  else if(Ex_QGP_search_mode==2){
    if(Ex_DEBUG){
      std::cout<<"QGP judge with max volume judge\n";
    }
    int id_x=-1,id_y=-1;
    double volume=energy_momentum.QGP_max_volume_eta0(id_x,id_y);
    if(volume<Ex_QGP_volume){
      //no QGP
      if(Ex_DEBUG){
        std::cout<<"no QGP generated\n";
        std::cout<<"max QGP volume: ";
        std::cout<<"max QGP volume "<<volume<<" begin at ("<<id_x<<","<<id_y<<")"<<std::endl;
        std::cout<<"sum of QGP volume :"<<energy_momentum.QGP_volume_sum()<<std::endl;
      }
      else std::cout<<volume<<" "<<0<<' '<<0<<std::endl;
      return 0;
    }
    else{
      remove_QGP_volume(secondaries,secondaries_cut,energy_momentum);
      if(Ex_DEBUG){
        std::cout<<"max QGP volume "<<volume<<" begin at ("<<id_x<<","<<id_y<<")"<<std::endl;
        std::cout<<"sum of QGP volume :"<<energy_momentum.QGP_volume_sum()<<std::endl;
      }
      else std::cout<<volume<<" ";
    }
  }
  //combine to oscar1997A format
  OSCAR_19(secondaries_cut);
  //combine to urqmd ftn14 format and freestreaming to t=0
  if(Ex_DEBUG){
    urqmd_14(secondaries_cut);
  }
  WriteFlow2(energy_momentum);
  if(Ex_DEBUG){
    std::cout<<"secondaries in QGP "<<secondaries.size()<<std::endl;
    std::cout<<"secondaries out of QGP "<<secondaries_cut.size()<<std::endl;
    std::cout<<"E and p_z in QGP :";
  }
  std::cout<<momentum_sum(secondaries,0)<<" "<<momentum_sum(secondaries,3);
}