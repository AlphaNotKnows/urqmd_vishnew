#include<stdlib.h>
#include<cmath>
#include"include/EPTensor.h"
namespace Transform{

  EPTensor::EPTensor(double x_down,double x_up,double y_down,double y_up,double eta_down,double eta_up,double tau_0,double K,unsigned x_bin,unsigned y_bin,unsigned eta_bin):x_down_(x_down),x_up_(x_up),y_down_(y_down),y_up_(y_up),eta_down_(eta_down),eta_up_(eta_up),tau_0_(tau_0),K_(K),x_bin_(x_bin),y_bin_(y_bin),eta_bin_(eta_bin),EP_(4,std::vector<Array3>(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(eta_bin,0))))),flow_(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(eta_bin,0)))){}

  // EPTensor::EPTensor(double x_down,double x_up,double y_down,double y_up,double eta_down,double eta_up,double tau_0,double K,unsigned x_bin,unsigned y_bin,unsigned eta_bin):x_down_(x_down),x_up_(x_up),y_down_(y_down),y_up_(y_up),eta_down_(eta_down),eta_up_(eta_up),tau_0_(tau_0),K_(K),x_bin_(x_bin),y_bin_(y_bin),eta_bin_(eta_bin),EP_(4,std::vector<Array3>(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(1,0))))),flow_(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(1,0)))){}

  void EPTensor::AddParticle(const Particle&particle){
    //determine the step
    double dx=(x_up_-x_down_)/(x_bin_-1);
    double dy=(y_up_-y_down_)/(y_bin_-1);
    double deta=(eta_up_-eta_down_)/(eta_bin_-1);
    //read the Minkow coordinate of particle
    double x0=particle.space().Minkow()[1];
    double y0=particle.space().Minkow()[2];
    double eta0=particle.space().Minkow()[3];
    //determine the bin range of particle
    unsigned x_down_bin=search_bin(x0-Ex_range*Ex_R_ver,x_down_,x_up_,x_bin_);
    unsigned x_up_bin=search_bin(x0+Ex_range*Ex_R_ver,x_down_,x_up_,x_bin_);
    unsigned y_down_bin=search_bin(y0-Ex_range*Ex_R_ver,y_down_,y_up_,y_bin_);
    unsigned y_up_bin=search_bin(y0+Ex_range*Ex_R_ver,y_down_,y_up_,y_bin_);
    unsigned eta_down_bin=search_bin(eta0-Ex_range*Ex_R_eta,eta_down_,eta_up_,eta_bin_);
    unsigned eta_up_bin=search_bin(eta0+Ex_range*Ex_R_eta,eta_down_,eta_up_,eta_bin_);
    //get the momentum in {tau,x,y,eta}, here the definition follow arxiv:1205.5019
    auto p0=particle.momentum().Minkow();
    double m_T=std::sqrt(p0[0]*p0[0]-p0[3]*p0[3]);
    double theta=particle.momentum().Milne()[0]-particle.space().Milne()[0];
    double p[4]={0};
    p[0]=m_T*std::cosh(theta);
    p[3]=m_T*std::sinh(theta)/tau_0_;
    p[1]=p0[1];p[2]=p0[2];
    //the overall factor
    double factor=K_/(p[0]*tau_0_*std::sqrt(2*Pi)*2*Pi*Ex_R_eta*Ex_R_ver*Ex_R_ver);
    //for particle influence region
    for(unsigned i=x_down_bin;i<=x_up_bin;i++){
      double delta_x=x_down_+i*dx-x0;
      for(unsigned j=y_down_bin;j<=y_up_bin;j++){
        double delta_y=y_down_+j*dy-y0;
        for(unsigned k=eta_down_bin;k<=eta_up_bin;k++){
        // for(unsigned k=0;k<1;k++){
          //calculator the factor local in x,y,eta
          double delta_eta=eta_down_+k*deta-eta0;
          // double delta_eta=eta0;
          double exponent=-( (delta_x*delta_x+delta_y*delta_y)/(2*Ex_R_ver*Ex_R_ver) + (delta_eta*delta_eta)/(2*Ex_R_eta*Ex_R_eta) );
          double local_factor=factor*std::exp(exponent);
          //loop over 4*4 tensor
          for(unsigned mu=0;mu<4;mu++){
            for(unsigned nu=0;nu<4;nu++){
              EP_[mu][nu][i][j][k]+=local_factor*p[mu]*p[nu];
            }
          }
        }
      }
    }
  }

  void EPTensor::CalFlow(){
    for(unsigned i=0;i<x_bin_;i++){
      for(unsigned j=0;j<y_bin_;j++){
        for(unsigned k=0;k<eta_bin_;k++){
          // for(unsigned k=0;k<1;k++){
          //store the T0\nu for simplicity
          double T0[4]={0};
          for(unsigned nu=0;nu<4;nu++){
            T0[nu]=EP_[0][nu][i][j][k];
          }
          if(T0[0]<=0)continue;
          //get local energy with P=1/3*e
          double M2=T0[1]*T0[1]+T0[2]*T0[2]+tau_0_*tau_0_*T0[3]*T0[3];
          //2D equation parameter
          double a=1,b=2*T0[0],c=3*(M2-T0[0]*T0[0]);
          flow_[0][i][j][k]=(-b+std::sqrt( b*b-4*a*c ))/2*a;
          //cal the T00+P,and remove the strange point
          double denominator=T0[0]+flow_[0][i][j][k]/3;
          if(denominator<0.01)continue;
          //get velocity
          flow_[1][i][j][k]=T0[1]/denominator;
          flow_[2][i][j][k]=T0[2]/denominator;
          flow_[3][i][j][k]=tau_0_*T0[3]/denominator;
        }
      }
    }
  }

  bool EPTensor::search_eta_cut(double eta_cut[],const double Edec) const{
    //eta_cut edge, LB[0],RB[1]
    int edge=0;
    eta_cut[0]=0,eta_cut[1]=-1;
    //determine the step
    double dx=(x_up_-x_down_)/(x_bin_-1);
    double dy=(y_up_-y_down_)/(y_bin_-1);
    double deta=(eta_up_-eta_down_)/(eta_bin_-1);
    for(int k=0;k<eta_bin_;k++){
      double eta=eta_down_+deta*k;
      for(int i=0;i<x_bin_;i++){
        bool goto_new_eta=false;
        for(int j=0;j<y_bin_;j++){
          if(EP_[0][0][i][j][k]>=Edec){
            goto_new_eta=true;
            if(Ex_DEBUG){
              std::cout<<"    (i,j,k)="<<i<<','<<j<<','<<k<<"  "<<"eta="<<eta<<"  "<<"ed="<<EP_[0][0][i][j][k]<<std::endl;
            }
            if(edge==0){
              eta_cut[0]=eta;eta_cut[1]=eta;
              edge=1;
            }
            else{
              eta_cut[1]=eta;
            }
            break;
          }
        }
        if(goto_new_eta)break;
      }
    }
    if(Ex_DEBUG){
      if(eta_cut[0]>eta_cut[1]){
        std::cout<<"all ed < Edec\n";
      }
      else{
        std::cout<<"judge eta_cut at LB,RB="<<eta_cut[0]<<" "<<eta_cut[1]<<std::endl;
      }
    }
    if(eta_cut[0]>eta_cut[1]){
      return false;
    }
    else return true;
  }

  void write2(const EPTensor&tensor,const std::string&output_path){
    for(unsigned comp=0;comp<4;comp++){
      //determine the output file name
      std::string output_file=output_path+"t0";
      output_file+=('0'+comp);
      output_file+=".txt";
      std::ofstream output(output_file.c_str(),std::ios::binary);
      for(unsigned i=0;i<Ex_M_bin[1];i++){
        for(unsigned j=0;j<Ex_M_bin[2];j++){
          //determine the eta=0 bin
          unsigned k=search_bin(0,Ex_M_down[3],Ex_M_up[3],Ex_M_bin[3]);
          // unsigned k=0;
          double middle=tensor[0][comp][i][j][k];
          output<<middle<<' ';
        }
        output<<std::endl;
      }
      output.close();
    }
  }

  void write(const EPTensor&tensor,const std::string&output_path){
    for(unsigned comp=0;comp<4;comp++){
      //determine the output file name
      std::string output_file=output_path+"t0";
      output_file+=('0'+comp);
      output_file+=".txt";
      std::ofstream output(output_file.c_str());
      for(unsigned i=0;i<Ex_M_bin[1];i++){
        for(unsigned j=0;j<Ex_M_bin[2];j++){
        //  for(unsigned k=0;k<Ex_M_bin[3];k++){
        for(unsigned k=0;k<1;k++){
          double middle=tensor[0][comp][i][j][k];
          output<<middle<<' ';
         }
        }
        output<<std::endl;
      }
      output.close();
    }
  }

  void WriteFlow2(const EPTensor&tensor,const std::string&output_path){
    auto flow=tensor.GetFlow();
    std::string output_file[3];
    output_file[0]=output_path+"ed.txt";
    output_file[1]=output_path+"u1.txt";
    output_file[2]=output_path+"u2.txt";
    for(unsigned comp=0;comp<3;comp++){
      std::ofstream output(output_file[comp].c_str());
      for(unsigned i=0;i<Ex_M_bin[1];i++){
        for(unsigned j=0;j<Ex_M_bin[2];j++){
          unsigned k=search_bin(0,Ex_M_down[3],Ex_M_up[3],Ex_M_bin[3]);
          // unsigned k=0;
          double middle;
          // if(comp==0)middle=flow[comp][i][j][k]/HbarC;
          // else middle=flow[comp][i][j][k];
          output<<flow[comp][i][j][k]<<' ';
        }
        output<<std::endl;
      }
      output.close();
    }
  }

}