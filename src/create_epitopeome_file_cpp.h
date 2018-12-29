#ifndef CREATE_EPITOPEOME_FILE_CPP_H
#define CREATE_EPITOPEOME_FILE_CPP_H

#include <map>
#include <string>

//' Creates a FASTA file with only the TMHs
//' @param tmhs_filename file that contains the TMHs as created by TMHMM
//' @param netmhc2pan_filename file that contains the NetMHC2pan results
//' @param epitopeome_filename name of the create epitopeome file, 
//'   saved in FASTA format
//' @return nothing
//' @author Richel J.C. Bilderbeek
// [[Rcpp::export]]
void create_epitopeome_file_cpp(
  const std::string& tmhs_filename,
  const std::string& netmhc2pan_filename,
  const std::string& epitopeome_filename
);

#endif // CREATE_EPITOPEOME_FILE_CPP_H



