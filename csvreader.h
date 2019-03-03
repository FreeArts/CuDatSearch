/*
 * CSVReader.h
 *
 *  Created on: 2019 jan. 24
 *      Author: freeart
 */
//In the future it will be on the Qt part
#ifndef CSVREADER_H_
#define CSVREADER_H_

#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

using namespace std;

class CSVReader
{

public:
    CSVReader(QString filename, QString delm = ";");
    virtual ~CSVReader();

    QString m_fileName_str;
    QString m_delimeter_str;

    // Function to fetch data from a CSV File
    QVector<QVector<QString> > getData();
};

#endif /* CSVREADER_H_ */