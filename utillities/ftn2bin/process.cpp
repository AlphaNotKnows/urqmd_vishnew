#include "process.h"
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

  void write_secondaries(std::ofstream&output,const std::vector<Particle>&secondaries){
    int num=secondaries.size();
    output.write((char*)&num,sizeof(num));
    for(int i=0;i<num;i++){
      output.write((char*)&secondaries[i],sizeof(secondaries[i]));
    }
  }

  void write_event(int event_num){
    for(int event_id=0;event_id<event_num;event_id++){
      std::string input_file="event";
      input_file+=std::to_string(event_id);
      std::cout<<"input "<<input_file;
      std::ifstream input(input_file.c_str());
      std::string output_file=input_file+"_bin.dat";
      std::ofstream output(output_file.c_str());
      int sample_number=0;
      std::vector<Particle>secondaries;
      while(get_secondaries(input,secondaries)){
        write_secondaries(output,secondaries);
        secondaries.clear();
        sample_number++;
      }
      std::cout<<" and write "<<output_file<<" with "<<sample_number<<" samples"<<std::endl;
    }
  }

  void first_particle(int event_id){
    std::string input_file="event";
    input_file+=std::to_string(event_id);
    std::string output_file=input_file+"first.txt";
    input_file+="_bin.dat";
    std::ifstream input(input_file.c_str());
    std::ofstream output(output_file.c_str());
    int secondaries_num=0;
    int sample_num=0;
    std::vector<Particle>secondaries;
    while(input.read((char*)&secondaries_num,sizeof(secondaries_num))&&!input.eof()){
      secondaries.clear();
      for(int i=0;i<secondaries_num;i++){
        double p[4]={0},x[4]={0};
        Particle this_particle(p,x,0,0);
        input.read((char*)&this_particle,sizeof(this_particle));
        secondaries.push_back(this_particle);
      }
      sample_num++;
      output<<"sample "<<sample_num<<std::endl;
      output<<secondaries[0]<<std::endl;
    }
  }



}
