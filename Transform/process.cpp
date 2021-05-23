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
    // CalBeta(beta);
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
        int itype,iso3,charge,parent,N_coll,parent_type;
        for(unsigned j=0;j<4;j++)input_line>>x[j];
        for(unsigned j=0;j<4;j++)input_line>>p[j];
        input_line>>mass>>itype>>iso3>>charge>>parent>>N_coll>>parent_type;
        // LorentzTransform(beta,p);
        // LorentzTransform(beta,x);
        for(int k=0;k<4;k++){
          p_sum[k]+=p[k];
        }
        //judge and push the particle on the surface,if the last time, let it all freestreaming
        Particle this_particle(p,x,mass,itype,iso3,charge,parent,N_coll,parent_type);
        double delta_t=-1;
        if(std::abs(this_particle.space().Minkow()[0]-Ex_M_up[0])<0.0001*Ex_Dx[0]){
          delta_t=cross_surface(this_particle,-1);
        }
        else{
          delta_t=cross_surface(this_particle);
        }
        if(delta_t>=0){
          Particle the=freestreaming(this_particle,delta_t);
          secondaries.push_back(the);
          // std::cout<<secondaries.size()<<':'<<secondaries[secondaries.size()-1].space().Milne()[0]<<' '<<the.space().Milne()[0]<<'\n';
          if(Ex_DEBUG){
            if(std::abs(the.space().Milne()[0]-Ex_Tau_0)>0.00001*Ex_Dx[0]){
              std::cout<<"delta_t="<<delta_t<<std::endl;
              // std::cout<<the<<std::endl;
            }
          }
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

  void remove_spectator(std::vector<Particle>&secondaries,std::vector<Particle>&secondaries_cut){
    auto ii=secondaries.begin();
    while(ii!=secondaries.end()){
      double eta=ii->space().Milne()[3];
      if(ii->GetN_coll()==0){
        secondaries_cut.push_back(*ii);
        secondaries.erase(ii);
      }
      else{
        ii++;
      }
    }
  }

  double search_energy(const std::string &input_file){
    double beta[4]={0};
    // CalBeta(beta);
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
        // LorentzTransform(beta,p);
        // LorentzTransform(beta,x);
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

  double remove_eta_cut(std::vector<Particle>&secondaries,std::vector<Particle>&secondaries_cut,const double* eta_cut){
    //energy within eta_cut
    double energy=0;
    double secondaries_num_sum=secondaries.size()+secondaries_cut.size();
    auto ii=secondaries.begin();
    while(ii!=secondaries.end()){
      double eta=ii->space().Milne()[3];
      if(eta<eta_cut[0]||eta>eta_cut[1]){
        secondaries_cut.push_back(*ii);
        secondaries.erase(ii);
      }
      else{
        ii++;
        energy+=ii->momentum().Minkow()[0];
      }
    }
    if(secondaries_num_sum!=(secondaries.size()+secondaries_cut.size())){
      std::cerr<<secondaries_num_sum<<' '<<secondaries.size()<<' '<<secondaries_cut.size()<<" eta cut is wrong"<<std::endl;
      exit(-1);
    }
    if(Ex_DEBUG){
      std::cout<<"secondaries within eta cut "<<secondaries.size()<<std::endl;
      std::cout<<"secondaries over eta cut "<<secondaries_cut.size()<<std::endl;
      std::cout<<"energy within eta cut "<<energy<<std::endl;
    }
    return energy;
  }

  double remove_QGP_volume(std::vector<Particle>&secondaries,std::vector<Particle>&secondaries_cut,const EPTensor&energy_momentum){
    //QGP energy
    double energy=0;
    double secondaries_num_sum=secondaries.size()+secondaries_cut.size();
    auto ii=secondaries.begin();
    while(ii!=secondaries.end()){
      int id[4]={0,0,0,0};
      for(int i=1;i<4;i++){
        id[i]=search_bin(ii->space().Milne()[i],Ex_M_down[i],Ex_M_up[i],Ex_M_bin[i]);
      }
      //if not belong to central fireball
      if(energy_momentum.Get_QGP_flag(id[1],id[2],id[3])<=0){
        secondaries_cut.push_back(*ii);
        secondaries.erase(ii);
      }
      else{
        energy+=ii->momentum().Minkow()[0];
        ii++;
      }
    }
    if(secondaries_num_sum!=(secondaries.size()+secondaries_cut.size())){
      std::cerr<<secondaries_num_sum<<' '<<secondaries.size()<<' '<<secondaries_cut.size()<<" eta cut is wrong"<<std::endl;
      exit(-1);
    }
    if(Ex_DEBUG){
      std::cout<<"secondaries within central QGP volume "<<secondaries.size()<<std::endl;
      std::cout<<"secondaries over central QGP volume "<<secondaries_cut.size()<<std::endl;
      std::cout<<"energy within central QGP volume "<<energy<<std::endl;
    }
    return energy;
  }

  void OSCAR_19(const std::vector<Particle>&secondaries,const std::string filename){
    using std::ios;
    using std::setw;
    using std::fixed;
    using std::setprecision;
    std::ofstream output(filename.c_str());
    if(!output){
      std::cerr<<"can't open "<<filename<<std::endl;
      exit(-1);
    }
    output<<"OSC1997A\n";
    output<<"final_id_p_x\n";
    output<<"   UrQMD  3.4       (  2,     1)+( 40,    18)  eqsp  0.1000E+10         1\n";
    //event header
    output.setf(ios::right);
    output.fill(' ');
    output.setf(ios::showpoint);
    output.flags(ios::fixed);
    output.flags(ios::scientific);
    output<< setw(10) << 1 << "  " << setw(10) << secondaries.size() << "  " << setw(8) << 0.0 << "  " << setw(8) << 0.0 << std::endl;

    //loop over particles
    for(int i=0;i<secondaries.size();i++){
      char line[500];
      sprintf(line,  "%24.16e  %24.16e  %24.16e  %24.16e  %24.16e  %24.16e  %24.16e  %24.16e  %24.16e",secondaries[i].momentum().Minkow()[1], secondaries[i].momentum().Minkow()[2], secondaries[i].momentum().Minkow()[3], secondaries[i].momentum().Minkow()[0], secondaries[i].GetMass(), secondaries[i].space().Minkow()[1],secondaries[i].space().Minkow()[2], secondaries[i].space().Minkow()[3], secondaries[i].space().Minkow()[0]);
      output<<setw(10)<<i+1<<"  ";
      output<<setw(10)<<secondaries[i].GetPdg()<<"  ";
      output<<line<<std::endl;
      // output<<setw(12)<<setprecision(6)<<secondaries[i].momentum().Minkow()[1]<<"  "<<secondaries[i].momentum().Minkow()[2]<<"  "<<secondaries[i].momentum().Minkow()[3]<<"  "<<secondaries[i].momentum().Minkow()[0]<<"  "<<secondaries[i].GetMass()<<"  "<<secondaries[i].space().Minkow()[1]<<"  "<<secondaries[i].space().Minkow()[2]<<"  "<<secondaries[i].space().Minkow()[3]<<"  "<<secondaries[i].space().Minkow()[0]<<"  \n";
    }
    output.close();

  }

  void urqmd_14(const std::vector<Particle>&secondaries,const std::string filename){
    using std::ios;
    using std::setw;
    using std::fixed;
    using std::setprecision;
    std::ofstream output(filename.c_str());
    output.setf(ios::right);
    output.fill(' ');
    output.setf(ios::showpoint);
    output.flags(ios::fixed);
    output.flags(ios::scientific);
    if(!output){
      std::cerr<<"can't open "<<filename<<std::endl;
      exit(-1);
    }
    std::ifstream header(Ex_input_file);
    while(true){
      std::string line;
      getline(header,line);
      output<<line<<std::endl;
      if(line.find("pvec")!=line.npos){
        break;
      }
    }
    header.close();
    output<<setw(12)<<secondaries.size()<<" 0"<<std::endl;
    for(int i=0;i<8;i++){
      output<<setw(8)<<0;
    }
    output<<std::endl;
    for(int i=0;i<secondaries.size();i++){
      Particle the(freestreaming(secondaries[i],-secondaries[i].space().Minkow()[0]));
      for(int j=0;j<4;j++){
        output<<" "<<setw(16)<<setprecision(8)<<the.space().Minkow()[j];
      }
      for(int j=0;j<4;j++){
        output<<" "<<setw(16)<<setprecision(8)<<the.momentum().Minkow()[j];
      }
      output<<" "<<setw(16)<<setprecision(8)<<the.GetMass();
      output<<setw(11)<<the.GetType();
      output<<setw(3)<<the.GetIso3()<<setw(3)<<the.GetCharge();
      output<<setw(9)<<the.GetParent()<<setw(5)<<the.GetN_coll()<<setw(4)<<the.GetParent_type()<<std::endl;
    }
    output.close();
  }

  double momentum_sum(const std::vector<Particle>&secondaries,int mu){
    double energy=0;
    for(int i=0;i<secondaries.size();i++){
      energy+=secondaries[i].momentum().Minkow()[mu];
    }
    return energy;
  }

  double momentum_Milne_sum(const std::vector<Particle>&secondaries,int mu){
    double energy=0;
    for(int i=0;i<secondaries.size();i++){
      auto p0=secondaries[i].momentum().Minkow();
      double eta_0=secondaries[i].space().Milne()[3];
      double cosh_eta=std::cosh(eta_0),sinh_eta=std::sinh(eta_0);
      double p[4]={0};
      p[0]=p0[0]*cosh_eta-p0[3]*sinh_eta;
      p[3]=(p0[3]*cosh_eta-p0[0]*sinh_eta)/Ex_Tau_0;
      p[1]=p0[1];p[2]=p0[2];
      energy+=p[mu];
    }
    return energy/Ex_Tau_0;
  }



}
