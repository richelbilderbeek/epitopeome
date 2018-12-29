#include "split_str_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_SeperateString)
{
  {
    { //Single input, seperator of type char
      const auto v = split_str("a",',');
      BOOST_CHECK(v.size() == 1);
      BOOST_CHECK(v[0]=="a");
    }
    { //Two inputs, seperator of type char
      const auto v = split_str("a,b",',');
      BOOST_CHECK(v.size() == 2);
      BOOST_CHECK(v[0]=="a");
      BOOST_CHECK(v[1]=="b");
    }
    {
      //Five inputs, seperator of type char
      const auto v = split_str("a,bb,ccc,dddd,eeeee",',');
      BOOST_CHECK(v.size() == 5);
      BOOST_CHECK(v[0]=="a");
      BOOST_CHECK(v[1]=="bb");
      BOOST_CHECK(v[2]=="ccc");
      BOOST_CHECK(v[3]=="dddd");
      BOOST_CHECK(v[4]=="eeeee");
    }
    { //Three inputs, of which one empty, seperator of type char
      const auto v = split_str("a, ,ccc",',');
      BOOST_CHECK(v.size() == 3);
      BOOST_CHECK(v[0]=="a");
      BOOST_CHECK(v[1]==" ");
      BOOST_CHECK(v[2]=="ccc");
    }
  }
}
