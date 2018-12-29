#ifndef CREATE_EPITOPEOME_CPP_H
#define CREATE_EPITOPEOME_CPP_H

#include <map>
#include <string>

//' Creates a FASTA file with only the TMHs
//' @param tmhs_filename file that contains the TMHs as created by TMHMM
//' @return nothing
//' @author Richel J.C. Bilderbeek
// [[Rcpp::export]]
std::map<std::string, std::string> create_epitopeome_cpp(
  const std::string& tmhs_filename,
  const std::string& netmhc2pan_filename
);

#endif // CREATE_EPITOPEOME_CPP_H



