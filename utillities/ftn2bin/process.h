#ifndef _PROCESS_H_
#define _PROCESS_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <string>
#include <sstream>
#include "Particle.h"
namespace Transform{
  extern double PI;
  /**remove the header in ftn13 file, if the file is end, return false*/
  bool remove_header(std::ifstream&input);
  /**get the all the secondaries in this event, if end of file, return false*/
  bool get_secondaries(std::ifstream&input);
  /**write the particle message as binary**/
  void write_secondaries(std::ofstream&output,const std::vector<Particle>&secondaries);
  /**write number of event to _bin.dat binary file*/
  void write_event(int event_num=0);
  // /**output the first particle in each sample in this event*/
  // void first_particle(int event_id);
}

#endif