#include "create_epitopeome_file_cpp.h"

#include <boost/test/unit_test.hpp>
#include <QFile>
#include <iostream>

BOOST_AUTO_TEST_CASE(epitopeome_file_must_be_created)
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

  const std::string result_filename = "tmp_epitiopeome.fasta";
  if (QFile::exists(result_filename.c_str()))
  {
    QFile::remove(result_filename.c_str());
  }
  assert(!QFile::exists(result_filename.c_str()));

  create_epitopeome_file_cpp(
    tmh_filename,
    netmhc2pan_filename,
    result_filename
  );
  BOOST_CHECK(QFile::exists(result_filename.c_str()));
  QFile::remove(result_filename.c_str());

}
