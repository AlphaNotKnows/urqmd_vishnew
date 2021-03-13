#include "include/Particle.h"
namespace Transform{

  double cross_surface(const Particle&particle,double dt,double tau_0){
    if(particle.space().Milne()[0]>tau_0)return -1;
    double gamma=particle.momentum().Minkow()[0];
    double velocity[4]={1,0,0,0};
    //calculate the velocity
    if(dt>0){
      for(unsigned i=1;i<4;i++){
        velocity[i]=particle.momentum().Minkow()[i]/gamma;
      }
      double x[4]={0};
      //calculate the final coordinate
      for(unsigned i=0;i<4;i++){
        x[i]=particle.space().Minkow()[i]+velocity[i]*dt;
      }
      //if can't cross
      if( (x[0]*x[0]-x[3]*x[3])<=tau_0*tau_0 )return -1;
    }
    //if can cross,calculate the cross coordinate
    //solve the 2d equation
    double a=1-velocity[3]*velocity[3];
    double b=2*(particle.space().Minkow()[0]-particle.space().Minkow()[3]*velocity[3]);
    double c=particle.space().Minkow()[0]*particle.space().Minkow()[0]-particle.space().Minkow()[3]*particle.space().Minkow()[3]-tau_0*tau_0;
    double dt1=(-b+std::sqrt(b*b-4*a*c))/(2*a);
    return dt1;
  }

  const Particle freestreaming(const Particle&particle,const double delta_t){
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
    return Particle(particle.momentum().Minkow(),x,particle.GetMass(),particle.GetType(),particle.GetIso3(),particle.GetCharge(),particle.GetParent(),particle.GetN_coll(),particle.GetParent_type());
  }

  std::ostream& operator<<(std::ostream&output,const Particle&this_particle){
    output<<"mass "<<this_particle.GetMass()<<','<<" type "<<this_particle.GetType()<<std::endl;
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