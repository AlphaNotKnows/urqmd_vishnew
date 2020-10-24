#include "Particle.h"
namespace Transform{
  Particle::Particle(double momentum[],double space[],double m,int itype,int iso3,int charge):p_(momentum),x_(space),m_(m),type_(itype),iso3_(iso3),charge_(charge){}

  std::ostream& operator<<(std::ostream&output,const Particle&this_particle){
    output<<"mass "<<this_particle.GetMass()<<','<<" type "<<this_particle.GetType()<<std::endl;
    output<<std::endl;
    output<<"Minkow";
    for(int i=0;i<4;i++){
      output<<' '<<this_particle.space().Minkow()[i];
    }
    output<<std::endl;
    return output;
  }
}