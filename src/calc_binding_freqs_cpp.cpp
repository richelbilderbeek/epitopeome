#include "calc_binding_freqs_cpp.h"

#include <cassert>

using namespace std;

///Calculate the halfdistance to the center of a TMH
///   m   ->         0
///  im   ->    -2,  0
///  imo  ->    -2,  0, 2
///  immo ->  -3, -1, 1, 3
/// immmo -> -4, -2, 0, 2, 4
///@param epitopeope one epitopeome sequence
///@return distances
std::vector<int> calc_distances(const std::string& epitopeope)
{
  if (epitopeope.empty()) return {};
  return {};
}

map<double, double> calc_binding_freqs_cpp(
  const vector<string>& epitopeome
)
{
  if (epitopeome.empty()) return {};
  //Number of counts (value) per half-distance(key)
  map<int, int> dist_cnt;
  for (int i = -100; i != 101; ++i)
  {
    dist_cnt.insert( { i, 0 } );
  }

  for (const std::string& s: epitopeome)
  {
    const std::vector<int> distances = calc_distances(s);
    for (const int d: distances) { ++dist_cnt[d]; }
  }

  map<double, double> m;
  for (const auto& p: dist_cnt)
  {
    assert(epitopeome.size() != 0);
    m.insert(
      {
        static_cast<double>(p.first / 2.0),
        static_cast<double>(p.second) / static_cast<double>(epitopeome.size())
      }
    );
  }
  return m;
}
