#include "create_tmh_locs_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>
BOOST_AUTO_TEST_CASE(test_tmh_file_must_have_4_exact_locs_cpp)
{
  const std::string tmh_filename = "tmhmm.txt";
  {
    QFile tmh_file(":/epitopeome/tmhmm.txt");
    tmh_file.copy(tmh_filename.c_str());
  }

  assert(QFile::exists(tmh_filename.c_str()));
  const auto locs = create_locatome_cpp(tmh_filename);
  BOOST_CHECK_EQUAL(locs.size() , 1);
  const std::string& key = (*locs.begin()).first;
  BOOST_CHECK(key == std::string("tr|I6WZ58|I6WZ58_MYCTU"));
  const std::string& value = (*locs.begin()).second;

/*
>tr|I6WZ58|I6WZ58_MYCTU Probable conserved transmembrane protein OS=Mycobacterium tuberculosis (strain ATCC 25618 / H37Rv) OX=83332 GN=Rv0713 PE=1 SV=1
MAGSDPPTGGPASQAGSDAGASPEHKHMSRRKHLVLDVCIILGVLIAYVFSLLGYDWLAH
TPGPLPQPDVGTTDDTVVLIRFEELHTVANRLDVKVLVLPDDSMIDHRLQVLTTDTSVRL
YPENELGDLQYPVGKLPAQVATTIEAHGNPGAWPFDTYTTDTVQADVLVGAGDNRQYVPA
RVEVTGSLEGWDISAVRVGESSQTSDRPDNVIITLKRAKGPLVFDLGICLVLITLPTLAL
FVAIQMITGRRKFQPPFGTWYAAMLFAVVPLRTILPGSPPAGAWIDRAVVIWVLIALAAA
MVVYIVAWYRESD
*/

/*
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	inside	     1    32
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	    33    55
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	outside	    56   221
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	   222   244
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	inside	   245   256
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	   257   274
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	outside	   275   288
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	   289   308
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	inside	   309   313
*/
  const std::string expected =
     std::string( 32 -   1 + 1, 'i')
   + std::string( 55 -  33 + 1, 't')
   + std::string(221 -  56 + 1, 'o')
   + std::string(244 - 222 + 1, 't')
   + std::string(256 - 245 + 1, 'i')
   + std::string(274 - 257 + 1, 't')
   + std::string(288 - 275 + 1, 'o')
   + std::string(308 - 289 + 1, 't')
   + std::string(313 - 309 + 1, 'i')
  ;

  const std::string expected_raw = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiitttttttttttttttttttttttooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooootttttttttttttttttttttttiiiiiiiiiiiittttttttttttttttttoooooooooooooottttttttttttttttttttiiiii"; //!OCLINT
  assert(expected == expected_raw);
  assert(expected.size() == 313);
  BOOST_CHECK_EQUAL(value.size(), 313);
  BOOST_CHECK_EQUAL(value, expected);
}
