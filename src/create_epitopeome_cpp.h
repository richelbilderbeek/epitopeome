#ifndef CREATE_EPITOPEOME_CPP_H
#define CREATE_EPITOPEOME_CPP_H

#include <map>
#include <string>

//' Creates an 'epitopeome' from a TMHMM and NetMHC2pan file
//' @param tmhs_filename file that contains the TMHs as created by TMHMM
//' @param netmhc2pan_filename file that contains the NetMHC2pan results
//' @return a map, with the sequence name as key, and its 'epitopeome'
//'   as value
//' @author Richel J.C. Bilderbeek
//' @export
// [[Rcpp::export]]
std::map<std::string, std::string> create_epitopeome_cpp(
  const std::string& tmhs_filename,
  const std::string& netmhc2pan_filename
);

#endif // CREATE_EPITOPEOME_CPP_H



