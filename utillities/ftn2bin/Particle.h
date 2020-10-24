#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <string>
#include <sstream>
#include "Vector4.h"
namespace Transform{

  ///particle class
  class Particle{
  private:
      ///four momentum
      Vector4 p_;
      ///four in space coordinate
      Vector4 x_;
      ///mass 
      double m_;
      ///particle type;
      int type_;
      ///I_3
      int iso3_;
      ///charge
      int charge_;
  public:
      Particle(double momentum[],double space[],double m,int itype,int iso3,int charge);
      /**return the momentum*/
      Vector4&momentum(){return p_;}
      /**return the space coordinate*/
      Vector4&space(){return x_;}
      /**return the momentum in const*/
      const Vector4&momentum() const{return p_;}
      /**return the space coordinate in const*/
      const Vector4&space() const{return x_;}
      /**return mass of particle*/
      double GetMass() const{return m_;}
      /**return particle type*/
      int GetType() const{return type_;}
      /**return charge*/
      int GetCharge() const{return charge_;}
      /**return ios3*/
      int GetIso3() const{return iso3_;}
  };

  /**output the particle information*/
  std::ostream&operator<<(std::ostream&output,const Particle&this_particle);
  /**remove the header of the file*/
  void remove_header(std::istream&input);
  /** expand particle in gaussian
   * 
   */
  void expand_particle();
  /** search the particle on tau_0
   * @para[in] input_file : the name of the data file
   * @para[in] output_file : the name of the output file
   */


}



#endif