/*
 * CSVReader.cpp
 *
 *  Created on: 2019 jan. 24
 *      Author: freeart
 */

#include "csvreader.h"

CSVReader::CSVReader(QString filename, QString delm)
    : m_fileName_str(filename), m_delimeter_str(delm) {
  m_dataBaseHeader_v.clear();
  m_dataList_v.clear();
}

CSVReader::~CSVReader() {}

void CSVReader::readData() {

  const unsigned int whereTheDataBaseHeader = 0;
  const unsigned int whereTheDataStart = 1;

  std::ifstream file(m_fileName_str.toStdString());
  std::vector<long int> l_tmpVector_v;
  std::vector<std::vector<std::string>> l_dataList_v;
  l_dataList_v.clear();

  std::string line = "";
  // Iterate through each line and split the content using delimeter
  while (getline(file, line)) {
    std::vector<std::string> vec;
    boost::algorithm::split(vec, line,
                            boost::is_any_of(m_delimeter_str.toStdString()));
    l_dataList_v.push_back(vec);
  }

  m_dataBaseHeader_v = l_dataList_v.at(whereTheDataBaseHeader);

  for (unsigned int l_itx_i = whereTheDataStart; l_itx_i < l_dataList_v.size();
       l_itx_i++) {
    for (unsigned int l_ity_i = 0; l_ity_i < l_dataList_v.at(l_itx_i).size();
         l_ity_i++) {
      long int l_tmpVectorValue_li =
          std::stol(l_dataList_v.at(l_itx_i).at(l_ity_i));
      l_tmpVector_v.push_back(l_tmpVectorValue_li);
    }
    m_dataList_v.push_back(l_tmpVector_v);
    l_tmpVector_v.clear();
  }
  // Close the File
  file.close();
}

std::vector<string> CSVReader::getHeaderOfDatabse() const {
  return m_dataBaseHeader_v;
}

std::vector<std::vector<long>> CSVReader::getDataBase() const {
  return m_dataList_v;
}
