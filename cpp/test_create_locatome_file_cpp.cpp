#include "create_locatome_file_cpp.h"

/* Nope, use R function tmhmm::run_tmhmm

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>

BOOST_AUTO_TEST_CASE(locatome_file_must_be_created)
{
  const std::string proteome_filename = "proteome.fasta";
  {
    QFile tmh_file(":/epitopeome/proteome.fasta");
    tmh_file.copy(proteome_filename.c_str());
  }
  assert(QFile::exists(proteome_filename.c_str()));

  const std::string result_filename = "tmp_locatome.fasta";
  if (QFile::exists(result_filename.c_str()))
  {
    QFile::remove(result_filename.c_str());
  }
  assert(!QFile::exists(result_filename.c_str()));

  create_locatome_file_cpp(
    proteome_filename,
    result_filename
  );
  BOOST_CHECK(QFile::exists(result_filename.c_str()));
  QFile::remove(result_filename.c_str());
}

*/
