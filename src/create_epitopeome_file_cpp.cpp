#include "create_epitopeome_file_cpp.h"
#include "create_epitopeome_cpp.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <vector>

using namespace std;

void create_epitopeome_file_cpp(
  const std::string& tmhs_filename,
  const std::string& netmhc2pan_filename,
  const std::string& epitopeome_filename
) {
  const std::map<std::string, std::string> epitopeome = create_epitopeome_cpp(
    tmhs_filename,
    netmhc2pan_filename
  );
  std::ofstream f(epitopeome_filename.c_str());
  std::map<std::string, std::string>::const_iterator i = epitopeome.begin();
  const std::map<std::string, std::string>::const_iterator j = epitopeome.end();
  for ( ; i != j; ++i)
  {
    const std::string& gene = (*i).first;
    f << ">" << gene << '\n';
    const std::string& epitopeon = (*i).second;
    f << epitopeon << '\n';
  }
}
