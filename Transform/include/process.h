#ifndef _PROCESS_H_
#define _PROCESS_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <string>
#include <sstream>
#include "transform.h"
#include "Vector4.h"
#include "Particle.h"
#include "EPTensor.h"
namespace Transform{

  /**print the result in 3 dim
   * @ para[in] output_file : output file name
   * @ para[in] tensor : result energy tensor
  */
  void print3(const std::string&output_file,const EPTensor&tensor);
  /**do Lorentz transformation from (p[0],p[1],p[2],p[3]) to (E,px,py,pz)*/
  void LorentzTransform(const double beta[4],double p[4]);
  /** remove the file header in urqmd file*/
  void remove_header(std::istream&input);
  /** calculate the sum of momentum and get (beta[0],beta)
   * @para[in] beta: the vector to store beta
   * @para[in] input_file : the name of the data file
  */
  void CalBeta(double beta[4],const std::string&input_file=Ex_input_file);
  /** search the particle on tau_0
   * @para[in] secondaries : the vector<Particle> which store all particles on tau_0
   * @para[in] input_file : the name of the data file
   * @ return the secondaries number at last time
   */
  unsigned search_tau(std::vector<Particle>&secondaries,const std::string&input_file=Ex_input_file);
  /** count the number of secondaries in each time step*/
  void secondaries_count(const std::string&input_file,const std::string&output_file);
  /** search the spectator
   * @para[in] secondaries : the vector store all secondaries
   * @para[in] output_path : the path to output the secondaries
   * @note the spectator will be removed from the secondaries
  */
  void search_spectator(std::vector<Particle>&secondaries,const std::string&output_path=Ex_output_path);
  /**search the energy at t0*/
  double search_energy(const std::string &input_file=Ex_input_file);
  /**remove all particles over eta_cut
   * @note use for eta_cut_mode==0
   * @para[in] secondaries: the vector to store all secondaries and will be remove all secondaries over eta_cut
   * @para[in] secondaries_cut: the vector to store all secondaries out of eta_cut
   * @para[in] eta_cut: LB[0]<RB[1]
   * @return the energy within eta_cut
  */
  double remove_eta_cut(std::vector<Particle>&secondaries,std::vector<Particle>&secondaries_cut,const double* eta_cut=Ex_eta_cut);
  /** remove all particles in the QGP fireball
   * @para[in] secondaries: the vector to store all secondaries and will be remove all secondaries over eta_cut
   * @para[in] secondaries_cut: the vector to store all secondaries out of eta_cut
   * @para[in] energy_momentum: the EPTensor that use to judge QGP fireball
   * @return the energy within QGP fireball
  */
  double remove_QGP_volume(std::vector<Particle>&secondaries,std::vector<Particle>&secondaries_cut,const EPTensor&energy_momentum);
  /**combine particle vector to oscar1997A format
   * @note the output particle are all on tau_0 surface
  */
  void OSCAR_19(const std::vector<Particle>&secondaries,const std::string filename=Ex_output_path+"eta_cut19.txt");
  /**combine particle vector to urqmd ftn14 format
   * @note the output particle are freestreaming to t=0
  */
  void urqmd_14(const std::vector<Particle>&secondaries,const std::string filename=Ex_output_path+"eta_cut14.txt");
  /**get the sum of momentum in the vector
   * @para[in] secondaries: the sum vector
   * @para[in] mu: the momentum component, 0~3
  */
  double momentum_sum(const std::vector<Particle>&secondaries,int mu);
  
}

#endif