#ifndef CALC_BINDING_FREQS_CPP_H
#define CALC_BINDING_FREQS_CPP_H

#include <map>
#include <string>
#include <vector>

//' Calculates the binding frequencies
//' @param epitopeome an epitopeome
//' @return a map, with the distance to the center of a TMH as its key, 
//'   and the fraction of peptides at that distance binding to MHC2
//' @author Richel J.C. Bilderbeek
//' @export
// [[Rcpp::export]]
std::map<int, double> calc_binding_freqs_cpp(
  const std::vector<std::string>& epitopeome
);

#endif // CALC_BINDING_FREQS_CPP_H
