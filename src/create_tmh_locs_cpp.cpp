#include "create_tmh_locs_cpp.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>

using namespace std;

std::map<std::string, std::vector<int> > create_tmh_locs_cpp(
  const std::string& tmhs_filename
) {
  std::map<std::string, std::vector<int> > m;

  std::ifstream file(tmhs_filename.c_str());

  for(string line; getline(file, line); )
  {
    std::istringstream iss(line);
    std::vector<std::string> words(
      (std::istream_iterator<std::string>(iss)),
      std::istream_iterator<std::string>()
    );
    assert(words.size() == 5);
    if (words[2] != std::string("TMhelix")) continue;
    const int from = atoi(words[3].c_str());
    const int to = atoi(words[4].c_str());
    const std::string key = words[0];
    if (m.find(key) == m.end())
    {
      m.insert(std::make_pair(key, std::vector<int>()));
    }
    assert(m.find(key) != m.end());
    (*m.find(key)).second.push_back(from);
    (*m.find(key)).second.push_back(to);
  }
  return m;
}
