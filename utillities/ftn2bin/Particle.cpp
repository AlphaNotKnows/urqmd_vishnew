#include "Particle.h"
namespace Transform{
  Particle::Particle(double momentum[],double space[],double m,int itype):p_(momentum),x_(space),m_(m),type_(itype){}


  const Particle freestreaming(Particle&particle,double delta_t){
    double gamma=particle.momentum().Minkow()[0];
    double velocity[4]={1,0,0,0};
    //calculate the velocity
    for(unsigned i=1;i<4;i++){
      velocity[i]=particle.momentum().Minkow()[i]/gamma;
    }
    double x[4]={0};
    for(unsigned i=0;i<4;i++){
      x[i]=particle.space().Minkow()[i]+velocity[i]*delta_t;
    }
    return Particle(particle.momentum().Minkow(),x,particle.mass(),particle.type());
  }

  std::ostream& operator<<(std::ostream&output,const Particle&this_particle){
    output<<"mass "<<this_particle.mass()<<','<<" type "<<this_particle.type()<<std::endl;
    output<<"velocity";
    double gamma=this_particle.momentum().Minkow()[0];
    for(int i=0;i<4;i++){
      output<<' '<<this_particle.momentum().Minkow()[i]/gamma;
    }
    output<<std::endl;
    output<<"Minkow";
    for(int i=0;i<4;i++){
      output<<' '<<this_particle.space().Minkow()[i];
    }
    output<<std::endl;
    return output;
  }
}