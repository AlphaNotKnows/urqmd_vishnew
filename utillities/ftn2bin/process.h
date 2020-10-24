#ifndef _PROCESS_H_
#define _PROCESS_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<string>
#include<sstream>
#include<set>
#include "Particle.h"
namespace Transform{
  extern double PI;
  extern const std::string all_event_file;
  // class which used to sort event 
  class Event{
  private:
    int id_;
    int secondaries_num_;
  public:
    Event(int id,int secondaries_num):id_(id),secondaries_num_(secondaries_num){}
    int GetId()const {return id_;}
    int GetSecondariesNum() const{return secondaries_num_;}
    bool operator<(const Event&the_event) const{return secondaries_num_==the_event.GetSecondariesNum()?id_<the_event.GetId():secondaries_num_<the_event.GetSecondariesNum();}
    bool operator>(const Event&the_event) const{return secondaries_num_==the_event.GetSecondariesNum()?id_>the_event.GetId():secondaries_num_>the_event.GetSecondariesNum();}
  };
  /**remove the header in ftn13 file, if the file is end, return false*/
  bool remove_header(std::ifstream&input);
  /**get the all the secondaries in this event, if end of file, return false*/
  bool get_secondaries(std::ifstream&input);
  /**write the particle message as binary**/
  void write_secondaries(std::ofstream&output,const std::vector<Particle>&secondaries);
  /**write number of event to _bin.dat binary file*/
  void write_event(int event_num=0);
  /**skip event num,start from 0 and if the event is too large, return false*/
  bool skip_event(int event_num,std::ifstream&input);
  /**search centrality range
   * @para[in] central_min : lower bound of centrality range
   * @para[in] central_max : upper bound
  */
  void search_central(std::ifstream&input,double central_min=0,double central_max=0.05);
  // /**output the first particle in each sample in this event*/
  // void first_particle(int event_id);
}

#endif