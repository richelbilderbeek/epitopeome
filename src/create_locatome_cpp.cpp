#include "create_locatome_cpp.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

std::map<std::string, std::string> create_locatome_cpp(
  const std::string& tmhs_filename
) {
  std::map<std::string, std::string> m;

  std::ifstream file(tmhs_filename.c_str());
  std::string last_key;

  for(string line; getline(file, line); )
  {
    assert(!line.empty());
    if (line[0] == '>') {
      //Must lose sequence description,
      //to match TMHMM and NetMHC2pan dictionary keys:
      //NetMHC2pan removes it
      std::istringstream iss(line);
          std::vector<std::string> words(
            (std::istream_iterator<std::string>(iss)),
            std::istream_iterator<std::string>()
          );
      assert(words.size() >= 1);
      last_key = words[0];
      //Lose starting '>'
      last_key = last_key.substr(1, last_key.size() - 1);
      m.insert(std::make_pair(last_key, std::string()));
      continue;
    }
    assert(m.find(last_key) != m.end());
    std::string sequence = line;
    std::string::iterator i = sequence.begin();
    const std::string::iterator j = sequence.end();
    for ( ; i != j; ++i)
    {
      *i = std::tolower(*i);
    }

    assert(m.find(last_key) != m.end());
    (*m.find(last_key)).second += sequence;
  }
  return m;
}
