#include "calc_binding_freqs_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>

BOOST_AUTO_TEST_CASE(no_sequence_empty_map)
{
  const auto m = calc_binding_freqs_cpp( { "" } );
  
  BOOST_CHECK(m.empty());
}
