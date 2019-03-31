/*
 * CSVReader.h
 *
 *  Created on: 2019 jan. 24
 *      Author: freeart
 */
// In the future it will be on the Qt part
#ifndef CSVREADER_H_
#define CSVREADER_H_

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>

#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

class CSVReader {

public:
  CSVReader(QString filename, QString delm = ";");
  virtual ~CSVReader();

  QString m_fileName_str;
  QString m_delimeter_str;

  // Function to fetch data from a CSV File
  std::vector<std::vector<string>> getData();
};

#endif /* CSVREADER_H_ */
