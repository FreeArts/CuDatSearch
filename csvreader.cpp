/*
 * CSVReader.cpp
 *
 *  Created on: 2019 jan. 24
 *      Author: freeart
 */

#include "csvreader.h"

CSVReader::CSVReader(QString filename, QString delm) :
    m_fileName_str(filename), m_delimeter_str(delm)
{ }

CSVReader::~CSVReader() {
    // TODO Auto-generated destructor stub
}

QVector<QVector<QString> > CSVReader::getData()
{
    QVector<QVector<QString> > l_dataList_v;
    l_dataList_v.clear();

    QFile file(m_fileName_str);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){

        return l_dataList_v;
    }


    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

         QStringList l_words = line.split(m_delimeter_str);
         l_dataList_v.push_back(l_words.toVector());
    }

    file.close();

    return l_dataList_v;
}

