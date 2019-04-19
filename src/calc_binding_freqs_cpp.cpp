#include "calc_binding_freqs_cpp.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <iterator>
#include <iostream>
#include <sstream>
using namespace std;

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
  const std::string& s
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
      ++i;
      j = i + 1;
      break;
    }
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
  return v;
}

map<double, double> calc_binding_freqs_cpp(
  vector<string> epitopeome
)
{
  if (epitopeome.empty()) return {};

  //Remove empty strings
  const auto new_end = std::remove_if(
    begin(epitopeome), end(epitopeome),
    [](const string& s)
    {
      return s.empty() || s[0] == '>';
    }
  );
  epitopeome.erase(new_end, end(epitopeome));
  if (epitopeome.empty()) return {};

  //Number of counts (value) per half-distance(key)
  //for all (bound and non-bound) peptides
  map<int, int> dist_cnt_all;
  //Number of counts (value) per half-distance(key)
  //for bound peptides
  map<int, int> dist_cnt_bound;
  const int min_dist{-500};
  const int max_dist{abs(min_dist)};
  for (int i = min_dist; i != max_dist + 1; ++i) // Too big, just to have all values
  {
    dist_cnt_all.insert( { i, 0 } );
    dist_cnt_bound.insert( { i, 0 } );
  }

  for (const std::string& s: epitopeome)
  {
    if (s.empty()) continue;
    if (s[0] == '>') continue;
    const std::vector<int> distances = calc_distances(s);
    assert(s.size() == distances.size());
    const int n = static_cast<int>(s.size());
    for (int i = 0; i != n; ++i)
    {
      ++dist_cnt_all[ distances[i] ];
      if (is_bound(s[i]))
      {
        assert(distances[i] >  min_dist);
        assert(distances[i] <= max_dist);
        ++dist_cnt_bound[ distances[i] ];
      }
    }
  }

  //Map that can hold all values
  //Key: distance, value: fraction of bounds AAs per all AAs
  map<double, double> m;
  for (const auto& p: dist_cnt_all)
  {
    //Number of half-distances
    const int n_hds{p.first};


    //Distance
    const double d{static_cast<double>(n_hds / 2.0)};


    const auto iter_n_bound{
      dist_cnt_bound.find(n_hds)
    };
    //If there is no bound AA at that half-distance, add it to m
    if (iter_n_bound == end(dist_cnt_bound))
    {
      m.insert( { d, 0.0 } );
      continue;
    }

    //Total number of AAs at that half-distance
    const int n_hits{p.second};

    //Total number of bound AAs at that half-distance
    const int n_bound{iter_n_bound->second};

    //If there are no hits, we assume there are zero bound there as well :-)
    if (n_hits == 0)
    {
      m.insert( { d, 0.0 } );
      continue;
    }

    //Fraction of AAs bound
    const double f_bound{
      static_cast<double>(n_bound) / static_cast<double>(n_hits)
    };
    assert(f_bound >= 0.0);
    assert(f_bound <= 1.0);

    m.insert( { d, f_bound } );
  }
  //Remove the empty tails of m, by copying it to n
  //Map that hold all relevant values
  //Key: distance, value: fraction of bounds AAs per all AAs
  const auto iter_begin = std::find_if(
    begin(m), end(m),
    [](const std::pair<double, double>& p) { return p.second > 0.0; }
  );
  if (iter_begin == end(m))
  {
    //There are no useful values
    return { { 0, 0.0} };
  }
  //Last useful value
  const auto iter_before_end = std::find_if(
    m.rbegin(), m.rend(),
    [](const std::pair<double, double>& p) { return p.second > 0.0; }
  );

  //const double first_useful_distance{iter_begin->first};
  assert(iter_begin != end(m));
  const double first_useful_count{iter_begin->second};

  assert(iter_before_end != m.rend());
  const double last_useful_distance{iter_before_end->first};
  const double last_useful_count{iter_before_end->second};
  assert(first_useful_count > 0.0);
  assert(last_useful_count > 0.0);
  auto iter_to_end = m.find(last_useful_distance);
  assert(iter_to_end->second > 0.0);
  ++iter_to_end;
  assert(iter_to_end->second == 0.0);

  //Map that can holds all useful values
  //Key: distance, value: fraction of bounds AAs per all AAs
  map<double, double> n;
  assert(iter_begin != iter_to_end);
  copy(iter_begin, iter_to_end, inserter(n, end(n)));

  if (n.empty())
  {
    n.insert( { 0, 0.0 } );
  }
  return n;
}
