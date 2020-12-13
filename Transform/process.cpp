#include "include/process.h"
namespace Transform{
  void remove_header(std::istream&input){
    std::string data_line;
    ///remove the header
    for(unsigned i=0;i<17;i++){
      getline(input,data_line);
      data_line.clear();
    }
  }

  void LorentzTransform(const double beta[4],double p[4]){
    double beta2=beta[1]*beta[1]+beta[2]*beta[2]+beta[3]*beta[3];
    double beta_p=beta[1]*p[1]+beta[2]*p[2]+beta[3]*p[3];
    double C=(beta[0]-1)/beta2;
    double E=p[0]*beta[0]-beta[0]*beta_p;
    double px=-beta[0]*beta[1]*p[0]+p[1]+C*beta[1]*beta_p;
    double py=-beta[0]*beta[2]*p[0]+p[2]+C*beta[2]*beta_p;
    double pz=-beta[0]*beta[3]*p[0]+p[3]+C*beta[3]*beta_p;
    p[0]=E,p[1]=px,p[2]=py,p[3]=pz;
  }

  void CalBeta(double beta[4],const std::string&input_file){
    std::ifstream input(input_file.c_str());
    std::string data_line;
    //remove the header
    remove_header(input);
    unsigned secondaries_num,cal_time;
    getline(input,data_line);
    std::stringstream input_line;
    input_line.str(data_line);
    input_line>>secondaries_num>>cal_time;
    //remove collision line
    getline(input,data_line);
    //only calculate the first time
    double p_sum[4]={0};
    for(unsigned i=0;i<secondaries_num;i++){
      //clear the stream
      input_line.clear();
      data_line.clear();
      ///get the data
      getline(input,data_line);
      input_line.str(data_line);
      double x[4],p[4];
      for(unsigned j=0;j<4;j++)input_line>>x[j];
      for(unsigned j=0;j<4;j++){
        input_line>>p[j];
        p_sum[j]+=p[j];
      }
    }
    for(int i=1;i<4;i++){
      beta[i]=p_sum[i]/p_sum[0];
    }
    beta[0]=1/std::sqrt(1-beta[1]*beta[1]-beta[2]*beta[2]-beta[3]*beta[3]);
    input.close();
  }
  
  unsigned search_tau(std::vector<Particle>&secondaries,const std::string&input_file){
    double beta[4]={0};
    CalBeta(beta);
    std::ifstream input(input_file.c_str());
    std::string data_line;
    //remove the header
    remove_header(input);
    //sum over all momentum in CMS
    double p_sum[4]={0};
    //count the time step in the input
    int time_step=0;
    unsigned secondaries_num,cal_time;
    while (getline(input,data_line)){
      //get the number of secondaries
      if(input.eof())break;
      time_step++;
      std::stringstream input_line;
      input_line.str(data_line);
      input_line>>secondaries_num>>cal_time;
      //remove collision line
      getline(input,data_line);
      for(unsigned i=0;i<secondaries_num;i++){
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
        LorentzTransform(beta,p);
        LorentzTransform(beta,x);
        for(int k=0;k<4;k++){
          p_sum[k]+=p[k];
        }
        //judge and push the particle on the surface,if the last time, let it all freestreaming
        Particle this_particle(p,x,mass,itype);
        double delta_t=-1;
        if(std::abs(this_particle.space().Minkow()[0]-Ex_M_up[0])<0.01*Ex_Dx[0]){
          delta_t=cross_surface(this_particle,10000*Ex_M_up[0]);
        }
        else{
          delta_t=cross_surface(this_particle);
        }
        if(delta_t>=0){
          secondaries.push_back(freestreaming(this_particle,delta_t));
        }
      }
    }
    for(int i=0;i<4;i++){
      p_sum[i]/=time_step;
    }
    // std::cout<<time_step<<std::endl;
    // for(int i=0;i<4;i++){
    //   std::cout<<p_sum[i]<<' ';
    // }
    // std::cout<<std::endl;
    input.close();
    return secondaries_num;
  }

  void secondaries_count(const std::string&input_file,const std::string&output_file){
    std::ifstream input(input_file.c_str());
    //write the secondaries counter to the end of history message
    std::ofstream output(output_file.c_str(),std::ios::app);
    // output.seekp(0,std::ios::end);
    std::string data_line;
    //remove the header
    remove_header(input);
    std::stringstream input_line;
    while (!input.eof())
    {
      input_line.clear();
      //get the number of secondaries
      getline(input,data_line);
      input_line.str(data_line);
      int secondaries_num,cal_time;
      input_line>>secondaries_num>>cal_time;
      //remove collision line
      output<<secondaries_num<<' ';
      getline(input,data_line);
      for(unsigned i=0;i<secondaries_num;i++){
        data_line.clear();
        ///get the data
        getline(input,data_line);
      }
    }
    output<<std::endl;
    input.close();
    output.close();
  }

  void search_spectator(std::vector<Particle>&secondaries,const std::string&output_path){
    unsigned i=0;
    const double fraction=0.9999;
    std::string output_file=output_path+"spectator.txt";
    std::ofstream output(output_file.c_str());
    while(true){
      if(i>=secondaries.size())break;
      //proton and neutron at high energy levels will also be treat as spectator
      if(secondaries[i].type()>=1&&secondaries[i].type()<=16){
        // if p_z/E>fraction, then treat the particle as spectator
        if(std::abs(secondaries[i].momentum().Minkow()[3]/secondaries[i].momentum().Minkow()[0])>=fraction){
          // for(unsigned j=0;j<4;j++){
          //   output<<secondaries[i].momentum().Minkow()[i]<<' ';
          // }
          // output<<endl;
          output<<secondaries[i];
          secondaries.erase(secondaries.begin()+i);
          continue;
        }
      }
      i++;
    }
    output.close();
  }

  double search_energy(const std::string &input_file){
    double beta[4]={0};
    CalBeta(beta);
    std::ifstream input(input_file.c_str());
    std::string data_line;
    //remove the header
    remove_header(input);
    unsigned secondaries_num,cal_time;
    double energy=0;
    double p_sum[4]={0};
    double x_sum[4]={0};
    while (getline(input,data_line)){
      //get the number of secondaries
      if(input.eof())break;
      std::stringstream input_line;
      input_line.str(data_line);
      input_line>>secondaries_num>>cal_time;
      //remove collision line
      getline(input,data_line);
      for(unsigned i=0;i<secondaries_num;i++){
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
        LorentzTransform(beta,p);
        LorentzTransform(beta,x);
        input_line>>mass>>itype;
        energy+=p[0];
        for(int k=1;k<4;k++){
          p_sum[k]+=p[k];
        }
      }
      break;
    }
    std::cout<<"px="<<p_sum[1]<<" py="<<p_sum[2]<<" pz="<<p_sum[3]<<std::endl;
    input.close();
    return energy;

  }



}
