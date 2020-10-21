#ifndef _PVECTOR4_H
#define _PVECTOR4_H
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <string>
#include <sstream>
namespace Transform{

  ///coordinate class
  class Vector4{
  private:
    ///Minkowski coordinate
    double x_[4];
    ///Milne coordinate
    double M_[4];
  public:
    /**initialize the coordinate*/
    Vector4(double x[]);
    /**Minkowski coordinate*/
    double*Minkow(){return x_;}
    /**Milne coordinate*/
    double*Milne(){return M_;}
    /**Minkowski coordinate in const*/
    const double*Minkow() const{return x_;}
    /**Milne coordinate in const*/
    const double*Milne() const{return M_;}
  };
  
}


#endif