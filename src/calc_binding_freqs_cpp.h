#ifndef CALC_BINDING_FREQS_CPP_H
#define CALC_BINDING_FREQS_CPP_H

#include <map>
#include <string>
#include <vector>

//' Calculates the binding frequencies
//' @param epitopeome an epitopeome, without protein names
//' @return a map,
//'   with the distance to the center of a TMH as its key
//'   (either x.0 or x.5),
//'   and the fraction of peptides at that distance binding to MHC2
//' @author Richel J.C. Bilderbeek
//' @export
// [[Rcpp::export]]
std::map<double, double> calc_binding_freqs_cpp(
  std::vector<std::string> epitopeome
);

std::vector<int> calc_distances(
  const std::string& epitopeope
);

#endif // CALC_BINDING_FREQS_CPP_H
