#include "calc_binding_freqs_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>


//calc_distances
BOOST_AUTO_TEST_CASE(calc_distances_empty)
{
  const auto v = calc_distances( "");
  BOOST_CHECK(v.empty());
}

BOOST_AUTO_TEST_CASE(calc_distances_one_tmh)
{
  const auto v = calc_distances( "m");
  BOOST_CHECK_EQUAL(v.size(), 1);
  BOOST_CHECK_EQUAL(v[0], 0);
}

BOOST_AUTO_TEST_CASE(calc_distances_two_tmh)
{
  const auto v = calc_distances("mm");
  BOOST_CHECK_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], -1);
  BOOST_CHECK_EQUAL(v[1],  1);
}

BOOST_AUTO_TEST_CASE(calc_distances_two_tmh_mix_left)
{
  const auto v = calc_distances("xm");
  BOOST_CHECK_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], -2);
  BOOST_CHECK_EQUAL(v[1],  0);
}

BOOST_AUTO_TEST_CASE(calc_distances_two_tmh_mix_right)
{
  const auto v = calc_distances("mx");
  BOOST_CHECK_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0],  0);
  BOOST_CHECK_EQUAL(v[1],  2);
}

BOOST_AUTO_TEST_CASE(calc_distances_three_tmhs)
{
  const auto v = calc_distances( "mmm");
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], -2);
  BOOST_CHECK_EQUAL(v[1],  0);
  BOOST_CHECK_EQUAL(v[2],  2);
}

BOOST_AUTO_TEST_CASE(calc_distances_three_tmhs_x_left)
{
  const auto v = calc_distances("xmm");
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], -3);
  BOOST_CHECK_EQUAL(v[1], -1);
  BOOST_CHECK_EQUAL(v[2],  1);
}

BOOST_AUTO_TEST_CASE(calc_distances_three_tmhs_x_mid)
{
  const auto v = calc_distances("mxm");
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0],  0);
  BOOST_CHECK_EQUAL(v[1], -2);
  BOOST_CHECK_EQUAL(v[2],  0);
}

BOOST_AUTO_TEST_CASE(calc_distances_three_tmhs_x_right)
{
  const auto v = calc_distances("mmx");
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], -1);
  BOOST_CHECK_EQUAL(v[1],  1);
  BOOST_CHECK_EQUAL(v[2],  3);
}

BOOST_AUTO_TEST_CASE(calc_distances_three_mix_tmhs_lr)
{
  const auto v = calc_distances("xmx");
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], -2);
  BOOST_CHECK_EQUAL(v[1],  0);
  BOOST_CHECK_EQUAL(v[2],  2);
}

BOOST_AUTO_TEST_CASE(calc_distances_four_tmhs)
{
  const auto v = calc_distances("mmmm");
  BOOST_CHECK_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v[0], -3);
  BOOST_CHECK_EQUAL(v[1], -1);
  BOOST_CHECK_EQUAL(v[2],  1);
  BOOST_CHECK_EQUAL(v[3],  3);
}

BOOST_AUTO_TEST_CASE(calc_distances_four_mix_tmhs)
{
  const auto v = calc_distances("xmmx");
  BOOST_CHECK_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v[0], -3);
  BOOST_CHECK_EQUAL(v[1], -1);
  BOOST_CHECK_EQUAL(v[2],  1);
  BOOST_CHECK_EQUAL(v[3],  3);
}

BOOST_AUTO_TEST_CASE(calc_distances_five_tmhs)
{
  const auto v = calc_distances("mmmmm");
  BOOST_CHECK_EQUAL(v.size(), 5);
  BOOST_CHECK_EQUAL(v[0], -4);
  BOOST_CHECK_EQUAL(v[1], -2);
  BOOST_CHECK_EQUAL(v[2],  0);
  BOOST_CHECK_EQUAL(v[3],  2);
  BOOST_CHECK_EQUAL(v[4],  4);
}

BOOST_AUTO_TEST_CASE(calc_distances_five_mix_tmhs)
{
  const auto v = calc_distances("mxmxm");
  BOOST_CHECK_EQUAL(v.size(), 5);
  BOOST_CHECK_EQUAL(v[0],  0);
  BOOST_CHECK_NE(v[1], 0);
  BOOST_CHECK_EQUAL(v[2],  0);
  BOOST_CHECK_NE(v[3], 0);
  BOOST_CHECK_EQUAL(v[4],  0);
}

BOOST_AUTO_TEST_CASE(calc_distances_one_x)
{
  const auto v = calc_distances( "x");
  BOOST_CHECK_EQUAL(v.size(), 1);
  BOOST_CHECK_NE(v[0], 0);
}


BOOST_AUTO_TEST_CASE(nothing_becomes_empty_map)
{
  const auto m = calc_binding_freqs_cpp( {} );
  BOOST_CHECK(m.empty());
}

BOOST_AUTO_TEST_CASE(one_empty_sequence_becomes_empty_map)
{
  const auto m = calc_binding_freqs_cpp( { "" } );
  BOOST_CHECK(m.empty());
}

BOOST_AUTO_TEST_CASE(sequence_one_non_bound)
{
  const auto m = calc_binding_freqs_cpp( { "m" } );
  BOOST_CHECK_EQUAL(m.size(), 1);
  BOOST_CHECK_EQUAL(m.begin()->first, 0);
  BOOST_CHECK_EQUAL(m.begin()->second, 0.0);
  BOOST_CHECK_EQUAL((*m.find(0)).second, 0.0);
}

BOOST_AUTO_TEST_CASE(sequence_one_bound)
{
  const auto m = calc_binding_freqs_cpp( { "M" } );
  BOOST_CHECK_EQUAL(m.size(), 1);
  BOOST_CHECK_EQUAL(m.begin()->first, 0);
  BOOST_CHECK_EQUAL(m.begin()->second, 1.0);
  BOOST_CHECK_EQUAL((*m.find(0)).second, 1.0);
}