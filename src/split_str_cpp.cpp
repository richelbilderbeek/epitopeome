#include "split_str_cpp.h"

#include <boost/algorithm/string/split.hpp>

std::vector<std::string> split_str(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(), seperator),
    boost::algorithm::token_compress_on);
  return v;
}
