#ifndef _EPTENSOR_H_
#define _EPTENSOR_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <string>
#include <sstream>
#include "transform.h"
#include "Vector4.h"
#include "Particle.h"
namespace Transform{

  /// a class transform PTensor to EPTensor
   class EPTensor{
  public:
    /**the array to store Energy Momentum Tensor*/
    typedef std::vector<std::vector<std::vector<double>>> Array3;
  private:
    double x_down_,x_up_,y_down_,y_up_,eta_down_,eta_up_,tau_0_,K_;
    unsigned x_bin_,y_bin_,eta_bin_;
    ///all EPTensor in 3d space, a (4*4*x*y*eta) tensor
    std::vector<std::vector<Array3>> EP_;
    ///search flag for QGP fireball
    std::vector<std::vector<std::vector<int>>>QGP_flag_;
    ///flow four velocity
    std::vector<Array3> flow_;
  public:
    /**initialize the EPTensor*/
    EPTensor(double x_down=Ex_M_down[1],double x_up=Ex_M_up[1],double y_down=Ex_M_down[2],double y_up=Ex_M_up[2],double eta_down=Ex_M_down[3],double eta_up=Ex_M_up[3],double tau_0=Ex_Tau_0,double K=Ex_K,unsigned x_bin=Ex_M_bin[1],unsigned y_bin=Ex_M_bin[2],unsigned eta_bin=Ex_M_bin[3]);
    /**content of EP*/
    const std::vector<std::vector<Array3>>&EnergyMomentum()const{return EP_;}
    /**EPTensor const index */
    const std::vector<Array3>&operator[](unsigned index) const{return EP_[index];}
    /**EPTensor index */
    std::vector<Array3>&operator[](unsigned index){return EP_[index];}
    /**get dx[mu] for 1:x 2:y 3:eta*/
    double Get_Dx(int mu)const;
    /** get flow in const*/
    const std::vector<Array3>&GetFlow()const{return flow_;}
    /**add particle to Energy Tensor*/ 
    void AddParticle(const Particle&particle);
    /**get momentum sum*/
    double momentum(const int mu)const;
    /**calculate four flow*/
    void CalFlow();
    /**search eta cut by searching the eta which all ed<Edec
     * @return if all ed < Edec, return false and eta[0]=0,eta[1]=-1
    */
    bool search_eta_cut(double eta_cut[],const double Edec=Ex_Edec) const;
    /**search flag for QGP fireball
     * @ note: 0:haven't search 1:over Edec -1:below Edec 
    */
    int Get_QGP_flag(int id_x,int id_y,int id_eta)const{return QGP_flag_[id_x][id_y][id_eta];}
    /** search QGP
     * @return volume of a connected QGP fireball which include (id_x,id_y,id_eta)
    */
    double QGP_fireball_search(const int id_x,const int id_y,const int id_eta,const double Edec=Ex_Edec);
    /**return the max QGP fireball volume include eta=0 point
     * @para[in] (id_x,id_y,0) is the point where max volume connected
    */
    double QGP_max_volume_eta0(int&id_x,int&id_y,const double Edec=Ex_Edec);
    /**return the sum of volume of grid which larger than Edec
     * @note only use after using QGP_max_volume_eta0
    */
    double QGP_volume_sum();
  };
  /**write EPTensor to t00.dat,t01.dat,t02.dat,t03.dat*/
  void write(const EPTensor&tensor,const std::string&output_path=Ex_output_path);
  /**write EPTensor to t00.dat,t01.dat,t02.dat,t03.dat with only eta=0*/
  void write2(const EPTensor&tensor,const std::string&output_path=Ex_output_path);
  /**write flow in 2d to ed.dat u1.dat u2.dat with only eta=0*/
  void WriteFlow2(const EPTensor&tensor,const std::string&output_path=Ex_output_path);
}


#endif