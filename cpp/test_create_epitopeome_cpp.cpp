#include "create_epitopeome_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>

BOOST_AUTO_TEST_CASE(locatome_must_be_exactly_cpp)
{
  const std::string tmh_filename = "tmhmm.txt";
  {
    QFile tmh_file(":/epitopeome/tmhmm.txt");
    tmh_file.copy(tmh_filename.c_str());
  }
  assert(QFile::exists(tmh_filename.c_str()));

  const std::string netmhc2pan_filename = "netmhc2pan.csv";
  {
    QFile tmh_file(":/epitopeome/netmhc2pan.csv");
    tmh_file.copy(netmhc2pan_filename.c_str());
  }
  assert(QFile::exists(netmhc2pan_filename.c_str()));

  const std::string locatome =
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
  std::string expected = locatome;
  const std::vector<int> begin_pos_human = { 210, 211, 212, 213, 214, 227, 228, 229, 230, 239, 240, 261, 262, 263, 264, 265};
  for (const int pos_human: begin_pos_human)
  {
    int i = pos_human - 1;
    const int j = i + 15;
    for ( ; i != j ; ++i)
    {
      expected[i] = std::toupper(expected[i]);
    }
  }
  const std::string expected_raw
  = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"
    "ttttttttttttttttttttttt"
    "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" //!OCLINT indeed long
  // 2
  // 1         2         3         4         5         6         7         8
  // 0123456789012345678901234567890123456789012345678901234567890123456789012345678 //!OCLINT indeed long
  // ***************  |           |                     |
  //  *************** |           |                     |
  //   ***************|           |                     |
  //    ***************           |                     |
  //     ***************          |                     |
  //                  ***************                   |
  //                   ***************                  |
  //                    ***************                 |
  //                     ***************                |
  //                              ***************       |
  //                               ***************      |
  //                                                    ***************
  //                                                     ***************
  //                                                      ***************
  //                                                       ***************
  //                                                        ***************
    "OOOOOOOOOOOOTTTTTTTTTTTTTTTTTTTTTTTIIIIIIIIIIiittttTTTTTTTTTTTTTTOOOOOooooooooo" //!OCLINT indeed long
    "ttttttttttttttttttttiiiii"
  ;
  assert(expected == expected_raw);

  const auto epitopeome = create_epitopeome_cpp(tmh_filename, netmhc2pan_filename);

  BOOST_CHECK_EQUAL(1, epitopeome.size());
  BOOST_CHECK_EQUAL(expected, (*epitopeome.begin()).second);
  /*
210,"NVIITLKRAKGPLVF","tr|I6WZ58|I6WZ58_MYCTU",1.4
211,"VIITLKRAKGPLVFD","tr|I6WZ58|I6WZ58_MYCTU",1.6
212,"IITLKRAKGPLVFDL","tr|I6WZ58|I6WZ58_MYCTU",1.2
213,"ITLKRAKGPLVFDLG","tr|I6WZ58|I6WZ58_MYCTU",1.9
214,"TLKRAKGPLVFDLGI","tr|I6WZ58|I6WZ58_MYCTU",5
227,"GICLVLITLPTLALF","tr|I6WZ58|I6WZ58_MYCTU",4.5
228,"ICLVLITLPTLALFV","tr|I6WZ58|I6WZ58_MYCTU",4
229,"CLVLITLPTLALFVA","tr|I6WZ58|I6WZ58_MYCTU",3.5
230,"LVLITLPTLALFVAI","tr|I6WZ58|I6WZ58_MYCTU",3.5
239,"ALFVAIQMITGRRKF","tr|I6WZ58|I6WZ58_MYCTU",4
240,"LFVAIQMITGRRKFQ","tr|I6WZ58|I6WZ58_MYCTU",4.5
261,"YAAMLFAVVPLRTIL","tr|I6WZ58|I6WZ58_MYCTU",4
262,"AAMLFAVVPLRTILP","tr|I6WZ58|I6WZ58_MYCTU",3.5
263,"AMLFAVVPLRTILPG","tr|I6WZ58|I6WZ58_MYCTU",3
264,"MLFAVVPLRTILPGS","tr|I6WZ58|I6WZ58_MYCTU",3.5
265,"LFAVVPLRTILPGSP","tr|I6WZ58|I6WZ58_MYCTU",5

>tr|I6WZ58|I6WZ58_MYCTU Probable conserved transmembrane protein OS=Mycobacterium tuberculosis (strain ATCC 25618 / H37Rv) OX=83332 GN=Rv0713 PE=1 SV=1
MAGSDPPTGGPASQAGSDAGASPEHKHMSRRKHLVLDVCIILGVLIAYVFSLLGYDWLAH
TPGPLPQPDVGTTDDTVVLIRFEELHTVANRLDVKVLVLPDDSMIDHRLQVLTTDTSVRL
YPENELGDLQYPVGKLPAQVATTIEAHGNPGAWPFDTYTTDTVQADVLVGAGDNRQYVPA
RVEVTGSLEGWDISAVRVGESSQTSDRPDNVIITLKRAKGPLVFDLGICLVLITLPTLAL
FVAIQMITGRRKFQPPFGTWYAAMLFAVVPLRTILPGSPPAGAWIDRAVVIWVLIALAAA
MVVYIVAWYRESD

tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	inside	     1    32
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	    33    55
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	outside	    56   221
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	   222   244
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	inside	   245   256
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	   257   274
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	outside	   275   288
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	TMhelix	   289   308
tr|I6WZ58|I6WZ58_MYCTU	TMHMM2.0	inside	   309   313

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

  const std::string expected_raw
  = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"
    "ttttttttttttttttttttttt"
    "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"  //!OCLINT indeed long
    "ttttttttttttttttttttttt"
    "iiiiiiiiiiii"
    "tttttttttttttttttt"
    "oooooooooooooo"
    "ttttttttttttttttttttiiiii"
  ;
*/

}
