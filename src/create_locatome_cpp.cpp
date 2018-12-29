#include "create_locatome_cpp.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <vector>

using namespace std;

std::map<std::string, std::string> create_locatome_cpp(
  const std::string& tmhs_filename
) {
  std::map<std::string, std::string> m;

  std::ifstream file(tmhs_filename.c_str());

  for(string line; getline(file, line); )
  {
    std::istringstream iss(line);
    std::vector<std::string> words(
      (std::istream_iterator<std::string>(iss)),
      std::istream_iterator<std::string>()
    );
    assert(words.size() == 5);
    const std::string location = words[2];
    const int from = atoi(words[3].c_str());
    const int to = atoi(words[4].c_str());
    const std::string key = words[0];
    if (m.find(key) == m.end())
    {
      m.insert(std::make_pair(key, std::string()));
    }
    char c = '?';
    if (location == std::string("TMhelix")) c = 't';
    if (location == std::string("inside")) c = 'i';
    if (location == std::string("outside")) c = 'o';
    assert(c != '?');
    const int sz = to - from + 1;
    assert(sz > 0);
    const std::string locatome_part = std::string(sz, c);
    assert(m.find(key) != m.end());
    (*m.find(key)).second += locatome_part;
  }
  return m;
}
