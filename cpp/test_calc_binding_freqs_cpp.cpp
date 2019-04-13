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

BOOST_AUTO_TEST_CASE(calc_distances_three_tmhs)
{
  const auto v = calc_distances( "mmm");
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], -2);
  BOOST_CHECK_EQUAL(v[1],  0);
  BOOST_CHECK_EQUAL(v[2],  2);
}

BOOST_AUTO_TEST_CASE(calc_distances_three_mix_tmhs)
{
  const auto v = calc_distances( "xmx");
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], -2);
  BOOST_CHECK_EQUAL(v[1],  0);
  BOOST_CHECK_EQUAL(v[2],  2);
}

BOOST_AUTO_TEST_CASE(calc_distances_five_tmhs)
{
  const auto v = calc_distances( "mmmmm");
  BOOST_CHECK_EQUAL(v.size(), 5);
  BOOST_CHECK_EQUAL(v[0], -4);
  BOOST_CHECK_EQUAL(v[1], -2);
  BOOST_CHECK_EQUAL(v[2],  0);
  BOOST_CHECK_EQUAL(v[3],  2);
  BOOST_CHECK_EQUAL(v[4],  4);
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
