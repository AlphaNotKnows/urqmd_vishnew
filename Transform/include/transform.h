#ifndef _TRANSFROM_H_
#define _TRANSFROM_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include <string>
#include <sstream>
namespace Transform{
///basic constants,all extern variables begin with Ex_
///surface tau_0
extern double Ex_Tau_0;
///R_ver
extern double Ex_R_ver;
/// R_eta
extern double Ex_R_eta;
/// Delta x^{\mu} in x coordinate
extern double Ex_Dx[4];
/// x^{\mu} range in Milne coordinate
extern double Ex_M_down[4];
extern double Ex_M_up[4];
/// bin in Minkow or Milne coordinate
extern unsigned Ex_M_bin[4];
/// the range factor of nucleon
extern double Ex_range;
/// name of input data file
extern std::string Ex_input_file;
/// path to record data
extern std::string Ex_output_path;
/// name of parameter file
extern std::string Ex_parameter_file;
/// normalization in EPTensor
extern double Ex_K;
/// Pi
extern const double Pi;
/**HbarC=GeV*fm*/
extern const double HbarC;
/**pause until input a enter*/
void pause();
/**get the dir_path of the file_path*/
const std::string get_dir(std::string path);
/**clear the space in the string*/
std::string& clear_space(std::string &str);
/**initialize all Ex parameters
 * @para[in] parameter_file : the file store the parameter, with default name parameter.dat
*/
void initialize(const std::string&parameter_file="parameter.dat");
/**print common parameters to insure that the parameter is not changed*/
void print_Ex();
  /** get the bin number of the x
   * @para[in] x : location
   * @para[in] x_down : low bound
   * @para[in] x_up ; up bound
   * @para[in] bin : bin number
   * @return the bin number of x
  */
  unsigned search_bin(double x,double x_down,double x_up,unsigned bin);
}


#endif