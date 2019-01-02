#include "create_locatome_file_cpp.h"
#include "create_locatome_cpp.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <vector>

using namespace std;

void create_locatome_file_cpp(
  const std::string& fasta_filename,
  const std::string& locatome_filename
) {
  const std::map<std::string, std::string> locatome = create_locatome_cpp(
    fasta_filename
  );
  std::ofstream f(locatome_filename.c_str());
  std::map<std::string, std::string>::const_iterator i = locatome.begin();
  const std::map<std::string, std::string>::const_iterator j = locatome.end();
  for ( ; i != j; ++i)
  {
    const std::string& gene = (*i).first;
    f << ">" << gene << '\n';
    const std::string& epitopeon = (*i).second;
    f << epitopeon << '\n';
  }
}
