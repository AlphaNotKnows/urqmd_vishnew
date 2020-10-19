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
  /** remove the file header in urqmd file*/
  void remove_header(std::istream&input);
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
}

#endif