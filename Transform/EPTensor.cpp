#include<stdlib.h>
#include<cmath>
#include"include/EPTensor.h"
namespace Transform{

  EPTensor::EPTensor(double x_down,double x_up,double y_down,double y_up,double eta_down,double eta_up,double tau_0,double K,unsigned x_bin,unsigned y_bin,unsigned eta_bin):x_down_(x_down),x_up_(x_up),y_down_(y_down),y_up_(y_up),eta_down_(eta_down),eta_up_(eta_up),tau_0_(tau_0),K_(K),x_bin_(x_bin),y_bin_(y_bin),eta_bin_(eta_bin),EP_(1,std::vector<Array3>(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(eta_bin,0))))),flow_(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(eta_bin,0)))),QGP_flag_(x_bin,std::vector<std::vector<int>>(y_bin,std::vector<int>(eta_bin,0))){}

  // EPTensor::EPTensor(double x_down,double x_up,double y_down,double y_up,double eta_down,double eta_up,double tau_0,double K,unsigned x_bin,unsigned y_bin,unsigned eta_bin):x_down_(x_down),x_up_(x_up),y_down_(y_down),y_up_(y_up),eta_down_(eta_down),eta_up_(eta_up),tau_0_(tau_0),K_(K),x_bin_(x_bin),y_bin_(y_bin),eta_bin_(eta_bin),EP_(4,std::vector<Array3>(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(1,0))))),flow_(4,Array3(x_bin,std::vector<std::vector<double>>(y_bin,std::vector<double>(1,0)))){}

  double EPTensor::Get_Dx(int mu)const{
    switch (mu)
    {
    case 1:return (x_up_-x_down_)/(x_bin_-1);
    case 2:return (y_up_-y_down_)/(y_bin_-1);
    case 3:return (eta_up_-eta_down_)/(eta_bin_-1);
    default:
      break;
    }
    if(mu<=0||mu>3){
      std::cerr<<"wrong id of Get_Dx\n";
      exit(-1);
    }
  }

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
    double eta_0=particle.space().Milne()[3];
    double cosh_eta=std::cosh(eta_0),sinh_eta=std::sinh(eta_0);
    double p[4]={0};
    p[0]=p0[0]*cosh_eta-p0[3]*sinh_eta;
    p[3]=(p0[3]*cosh_eta-p0[0]*sinh_eta)/tau_0_;
    p[1]=p0[1];p[2]=p0[2];
    // std::cout<<"p= ";
    // for(int i=0;i<4;i++){
    //   std::cout<<p[i]<<' ';
    // }
    // std::cout<<std::endl;
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
          //loop over T^{0,nu} tensor
          for(unsigned mu=0;mu<1;mu++){
            for(unsigned nu=0;nu<4;nu++){
              EP_[mu][nu][i][j][k]+=local_factor*p[mu]*p[nu];
              if(!std::isfinite(EP_[mu][nu][i][j][k])){
                if(Ex_DEBUG){
                  std::cerr<<"wrong EPTensor\n";
                  std::cerr<<eta_0<<' '<<eta_0<<' '<<p[mu]<<' '<<p[nu]<<std::endl;
                  std::cerr<<particle<<std::endl;
                }
                exit(-1);
              }
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

  double EPTensor::momentum(const int mu)const{
    double p=0;
    for(int i=0;i<x_bin_;i++){
      for(int j=0;j<y_bin_;j++){
        for(int k=0;k<eta_bin_;k++){
          p+=EP_[0][mu][i][j][k];
        }
      }
    }
    return p*Ex_Dx[1]*Ex_Dx[2]*Ex_Dx[3];
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
          if(flow_[0][i][j][k]>=Edec){
            goto_new_eta=true;
            if(Ex_DEBUG){
              std::cout<<"    (i,j,k)="<<i<<','<<j<<','<<k<<"  "<<"eta="<<eta<<"  "<<"ed="<<flow_[0][i][j][k]<<std::endl;
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


  double EPTensor::QGP_fireball_search(const int id_x,const int id_y,const int id_eta,const double Edec){
    //search direction
    static const int rx[6]={1,-1,0,0,0,0};
    static const int ry[6]={0,0,1,-1,0,0};
    static const int reta[6]={0,0,0,0,1,-1};
    static const double dV=Get_Dx(1)*Get_Dx(2)*Get_Dx(3);
    //have searched
    if(QGP_flag_[id_x][id_y][id_eta]!=0)return 0;
    //no QGP
    if(flow_[0][id_x][id_y][id_eta]<Edec){
      QGP_flag_[id_x][id_y][id_eta]=-1;
      return 0;
    }
    
    else{
      double volume=dV;
      QGP_flag_[id_x][id_y][id_eta]=1;
      for(int id=0;id<6;id++){
        int i=id_x+rx[id],j=id_y+ry[id],k=id_eta+reta[id];
        if((i>=0)&&(i<x_bin_)&&(j>=0)&&(j<y_bin_)&&(k>=0)&&(k<eta_bin_)){
          volume+=QGP_fireball_search(i,j,k);
        }
      }
      return volume;
    }
  }

  double EPTensor::QGP_max_volume_eta0(int&id_x,int&id_y,const double Edec){
    double volume=0;
    for(int i=0;i<x_bin_;i++){
      for(int j=0;j<y_bin_;j++){
        //determine the eta=0 bin
        unsigned k=search_bin(0,Ex_M_down[3],Ex_M_up[3],Ex_M_bin[3]);
        double volume_this=QGP_fireball_search(i,j,k,Edec);
        if(volume<volume_this){
          volume=volume_this;
          id_x=i;
          id_y=j;
        }
      }
    }
    return volume;
  }

  double EPTensor::QGP_volume_sum(){
    int n=0;
    static const double dV=Get_Dx(1)*Get_Dx(2)*Get_Dx(3);
    for(int i=0;i<x_bin_;i++){
      for(int j=0;j<y_bin_;j++){
        for(int k=0;k<eta_bin_;k++){
          if(QGP_flag_[i][j][k]==1){
            n++;
          }
        }
      }
    }
    return n*dV;
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