#include "calc_binding_freqs_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>

BOOST_AUTO_TEST_CASE(no_sequence_empty_map)
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
