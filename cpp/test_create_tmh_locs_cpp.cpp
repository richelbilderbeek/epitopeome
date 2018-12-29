#include "create_tmh_locs_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>

BOOST_AUTO_TEST_CASE(test_tmh_file_must_have_4_exact_locs_cpp)
{
  {
    QFile tmh_file(":/tmhprot/tmhmm.txt");
    tmh_file.copy("tmhmm.txt");
  }

  const auto locs = create_tmh_locs_cpp("tmhmm.txt");
  BOOST_CHECK(locs.size() == 1);
  const std::string& key = (*locs.begin()).first;
  BOOST_CHECK(key == std::string("tr|I6WZ58|I6WZ58_MYCTU"));
  const std::vector<int>& value = (*locs.begin()).second;
  BOOST_CHECK(value.size() == 8);
  BOOST_CHECK(value[0] == 33);
  BOOST_CHECK(value[1] == 55);
  BOOST_CHECK(value[2] == 222);
  BOOST_CHECK(value[3] == 244);
  BOOST_CHECK(value[4] == 257);
  BOOST_CHECK(value[5] == 274);
  BOOST_CHECK(value[6] == 289);
  BOOST_CHECK(value[7] == 308);
}
