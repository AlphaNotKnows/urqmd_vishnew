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
  public:
      Particle(double momentum[],double space[],double m,int itype);
      /**return the momentum*/
      Vector4&momentum(){return p_;}
      /**return the space coordinate*/
      Vector4&space(){return x_;}
      /**return the momentum in const*/
      const Vector4&momentum() const{return p_;}
      /**return the space coordinate in const*/
      const Vector4&space() const{return x_;}
      /**return mass of particle*/
      double mass() const{return m_;}
      /**return particle type*/
      int type() const{return type_;}
  };

  /**if freestreaming, return a particle freestream for dt
   * @para[in] particle : the freestreaming particle
   * @para[in] delta_t : freestreaming time
   * @return final_particle : a particle after freestreaming
   */
  const Particle freestreaming(Particle&particle,double delta_t);
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