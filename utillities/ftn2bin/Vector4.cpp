#include "Vector4.h"
namespace Transform{
  Vector4::Vector4(double x[]){
    for(int i=0;i<4;i++)x_[i]=x[i];
    double tau2=x[0]*x[0]-x[3]*x[3];
    if(tau2>=0){
      M_[0]=sqrt(tau2);
    }
    else{
      M_[0]=-sqrt(-tau2);
    }

    M_[3]=0.5*log( (x[0]+x[3])/(x[0]-x[3]) );
    M_[1]=x[1];M_[2]=x[2];
  }
}