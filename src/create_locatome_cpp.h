#ifndef CREATE_LOCATOME_CPP_H
#define CREATE_LOCATOME_CPP_H

#include <map>
#include <string>

//' Creates a FASTA file with only the TMHs for a TMHMM file
//' as created by a locally installled TMHMM binary
//' @param tmhs_filename file that contains the TMHs
//'   as created by a locally installed TMHMM binary
//' @return a dictionary with sequence names as key,
//'   and a 'locatome' as values.
//' @author Richel J.C. Bilderbeek
//' @export
// [[Rcpp::export]]
std::map<std::string, std::string> create_locatome_cpp(
  const std::string& tmhs_filename
);

#endif // CREATE_LOCATOME_CPP_H



