#include "calc_binding_freqs_cpp.h"

#include <cassert>
#include <numeric>
#include <iterator>
#include <iostream>
#include <sstream>
using namespace std;

void print(const std::vector<int>& v, std::ostream& os = std::cout)
{
  if (v.empty()) return;
  const int n = v.size();
  stringstream s;
  for (int i = 0; i != n - 1; ++i)
  {
    s << v[i] << ", ";
  }
  s << v[n - 1];
  os << s.str() << '\n';
}

bool is_bound(const char c) noexcept
{
  return c == 'I' || c == 'M' || c == 'O';
}

bool is_tmh(const char c) noexcept
{
  return c == 'm' || c == 'M';
}

///Calculate the halfdistance to the center of a TMH
///   m   ->         0
///  im   ->    -2,  0
///  imo  ->    -2,  0, 2
///  immo ->  -3, -1, 1, 3
/// immmo -> -4, -2, 0, 2, 4
///@param epitopeope one epitopeome sequence
///@return distances
std::vector<int> calc_distances(
  const std::string& s,
  const bool verbose
)
{
  if (s.empty()) return {};
  const int n = static_cast<int>(s.size());
  assert(n > 0);

  //Half-distances
  const int indermined{n + 3}; //+2, just to be sure, could maybe also be +1 or +0
  std::vector<int> v(n, indermined);

  for (int i = 0; i < n; ++i)
  {
    //Find first TMH,
    //must be a TMH ...
    if (!is_tmh(s[i])) continue;
    //and before it must be a non-TMH
    if (i > 0 && is_tmh(s[i - 1])) continue;
    assert(is_tmh(s[i]));

    for (int j = i; j < n; ++j)
    {
      //Find last TMH,
      //must be a TMH ...
      if (!is_tmh(s[j])) continue;
      //and after it must be a non-TMH
      if (j < n - 1 && is_tmh(s[j + 1])) continue;

      assert(is_tmh(s[j]));

      const int delta = j - i;
      const int half_dist = delta;
      v[i] = -half_dist;
      v[j] =  half_dist;
      if (verbose)
      {
        std::cout << "Hit (i = " << i << ", j = " << j << "):\n";
        print(v);
      }
      ++i;
      j = i + 1;
      break;
    }
  }
  if (verbose)
  {
    std::cout << "Midpoints:\n";
    print(v);
  }
  //Go forward, set shorter distance
  //  *  * -4  *  *  *  4  *  *
  //  *  * -2 -2  0  2  4  6  8
  for (int i = 1; i != n; ++i)
  {
    const int left = std::abs(v[i - 1]);
    const int here = std::abs(v[i]);
    if (here > left) v[i] = v[i - 1] + 2;
  }
  if (verbose)
  {
    std::cout << "Forward:\n";
    print(v);
  }
  //Go backward, set shorter distance
  //  *  * -4 -2  0  2  4  6  8
  // -8 -6 -4 -2  0  2  4  6  8
  for (int i = n - 2; i >= 0; --i)
  {
    assert(i >= 0);
    assert(i + 1 < static_cast<int>(v.size()));
    const int right = std::abs(v[i + 1]);
    const int here = std::abs(v[i]);
    //if (here > right) v[i] = v[i + 1] - 2;
    if (abs(here - right) > 2) v[i] = v[i + 1] - 2;
  }
  if (verbose)
  {
    std::cout << "Final:\n";
    print(v);
  }
  return v;
}

map<double, double> calc_binding_freqs_cpp(
  const vector<string>& epitopeome
)
{
  if (epitopeome.empty()) return {};
  {
    const int n_aas{
      accumulate(
        begin(epitopeome),
        end(epitopeome),
        0,
        [](const int i, const string& s) { return i + static_cast<int>(s.size()); }
      )
    };
    if (!n_aas) return {};
  }
  //Number of counts (value) per half-distance(key)
  map<int, int> dist_cnt;
  for (int i = -100; i != 101; ++i) // Too big, just to have all values
  {
    dist_cnt.insert( { i, 0 } );
  }

  for (const std::string& s: epitopeome)
  {
    const std::vector<int> distances = calc_distances(s);
    assert(s.size() == distances.size());
    const int n = static_cast<int>(s.size());
    for (int i = 0; i != n; ++i)
    {
      if (is_bound(s[i]))
      {
        assert(distances[i] > -100);
        assert(distances[i] <= 100);
        ++dist_cnt[ distances[i] ];
      }
    }
  }

  map<double, double> m;
  for (const auto& p: dist_cnt)
  {
    if (p.second) //Only use counts of non-zero
    {
      assert(epitopeome.size() != 0);
      m.insert(
        {
          static_cast<double>(p.first / 2.0),
          static_cast<double>(p.second) / static_cast<double>(epitopeome.size())
        }
      );
    }
  }
  if (m.empty())
  {
    m.insert( { 0, 0.0 } );
  }
  return m;
}
