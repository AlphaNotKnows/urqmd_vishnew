#include "process.h"
#include "Particle.h"
namespace Transform{
  
  bool remove_header(std::ifstream&input){
    std::string data_line;
    ///remove the header
    for(unsigned i=0;i<17;i++){
      getline(input,data_line);
      if(input.eof())return false;
      data_line.clear();
    }
    return true;
  }

  bool get_secondaries(std::ifstream&input,std::vector<Particle>&secondaries){
    if(!remove_header(input))return false;
    std::string data_line;
    std::stringstream input_line;
    // get the secondaries number
    getline(input,data_line);
    input_line.str(data_line);
    unsigned secondaries_num;
    input_line>>secondaries_num;
    // remove collision line
    input_line.clear();
    data_line.clear();
    getline(input,data_line);
    input_line.str(data_line);
    // begin get particle data
    for(int i=0;i<secondaries_num;i++){
      //clear the stream
        input_line.clear();
        data_line.clear();
        ///get the data
        getline(input,data_line);
        input_line.str(data_line);
        double x[4],p[4],mass;
        int itype;
        for(unsigned j=0;j<4;j++)input_line>>x[j];
        for(unsigned j=0;j<4;j++)input_line>>p[j];
        input_line>>mass>>itype;
        //judge and push the particle on the surface,if the last time, let it all freestreaming
        secondaries.push_back(Particle(p,x,mass,itype));
    }
    return true;
  }



}
