#ifndef SPLIT_STR_CPP_H
#define SPLIT_STR_CPP_H

#include <string>
#include <vector>

//' Split a string
//' @param input the input string
//' @param seperator the seperator
//' @return a vector of strings
//' @author Richel J.C. Bilderbeek
// [[Rcpp::export]]
std::vector<std::string> split_str(
  const std::string& input,
  const char seperator
);

#endif // SPLIT_STR_CPP_H



