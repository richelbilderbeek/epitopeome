#ifndef CREATE_LOCATOME_CPP_H
#define CREATE_LOCATOME_CPP_H

#include <map>
#include <string>

//' Creates a FASTA file with only the TMHs
//' @param tmhs_filename file that contains the TMHs as created by TMHMM
//' @return nothing
//' @author Richel J.C. Bilderbeek
// [[Rcpp::export]]
std::map<std::string, std::string> create_locatome_cpp(
  const std::string& tmhs_filename
);

#endif // CREATE_LOCATOME_CPP_H



