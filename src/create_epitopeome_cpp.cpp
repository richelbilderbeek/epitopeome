#include "create_epitopeome_cpp.h"
#include "create_locatome_cpp.h"
#include "split_str_cpp.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

std::map<std::string, std::string> create_epitopeome_cpp(
  const std::string& tmhs_filename,
  const std::string& netmhc2pan_filename
) {
  const std::map<std::string, std::string> locatome = create_locatome_cpp(tmhs_filename);

  std::map<std::string, std::string> m = locatome;

  std::ifstream file(netmhc2pan_filename.c_str());

  for(string line; getline(file, line); )
  {
    //Skip header
    if (line == "\"Pos\",\"Peptide\",\"ID\",\"Allele\",\"one_minus_log50k\",\"nM\",\"Rank\"") continue;
    const std::vector<std::string> words = split_str(line, ',');
    assert(words.size() == 7);
    const int pos = std::atoi(words[0].c_str());
    //const std::string peptide = words[1];
    const std::string quoted_id = words[2];
    const std::string id = quoted_id.substr(1, quoted_id.size() - 2);
    assert(m.find(id) != m.end());
    std::string& s = (*m.find(id)).second;
    int i = pos - 1;
    const int j = i + 15;
    for ( ; i != j ; ++i)
    {
      s[i] = std::toupper(s[i]);
    }
  }
  return m;
}
