#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <string>
#include <sstream>
#include "transform.h"
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
      int iso3_;
      int charge_;
      int parent_;
      int N_coll_;
      int parent_type_;
  public:
      Particle(const Particle&the):p_(the.momentum()),x_(the.space()),m_(the.GetMass()),type_(the.GetType()),iso3_(the.GetIso3()),charge_(the.GetCharge()),parent_(the.GetParent()),N_coll_(the.GetN_coll()),parent_type_(the.GetParent_type()){}
      Particle(const double momentum[],const double space[],const double m,const int itype,const int iso3,const int charge,const int parent,const int N_coll,const int parent_type):p_(momentum),x_(space),m_(m),type_(itype),iso3_(iso3),charge_(charge),parent_(parent),N_coll_(N_coll),parent_type_(parent_type){}
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
      /**return urqmd particle type*/
      int GetType() const{return type_;}
      int GetIso3() const{return iso3_;}
      int GetCharge() const{return charge_;}
      int GetParent() const{return parent_;}
      int GetN_coll() const{return N_coll_;}
      int GetParent_type() const{return parent_type_;}
      int GetPdg() const {int a=type_,b=iso3_;return pdgid_(&a,&b);}
  };

  /**judge if freestreaming, whether the particle(tau<tau_0) will cross the surface, if cross, change the particle information, 
   * @para[in] particle : the particle
   * @para[in] dt : time step
   * @para[in] tau_0 : constant
   * @return dt1 if cross ,return cross dt1>=0, else return dt1 =-1
  */
  double cross_surface(const Particle&particle,double dt=Ex_Dx[0],double tau_0=Ex_Tau_0);
  /**if freestreaming, return a particle freestream for dt
   * @para[in] particle : the freestreaming particle
   * @para[in] delta_t : freestreaming time
   * @return final_particle : a particle after freestreaming
   * @note : if dt<=0, means the particle can freezeout infinity time
   */
  const Particle freestreaming(const Particle&particle,const double delta_t);
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