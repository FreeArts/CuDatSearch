/*
 * CSVReader.cpp
 *
 *  Created on: 2019 jan. 24
 *      Author: freeart
 */

#include "csvreader.h"
#include "select.h"
CSVReader::CSVReader(QString filename, QString delm) :
    m_fileName_str(filename), m_delimeter_str(delm)
{ }

CSVReader::~CSVReader() {

}

//OLD
/*std::vector<std::vector<std::string> > CSVReader::getData()
{
    //QVector<QVector<QString> > l_dataList_v;
    std::vector<std::vector<std::string> > l_dataList_v;
    l_dataList_v.clear();

    QFile file(m_fileName_str);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){

        return l_dataList_v;
    }


    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        QStringList l_words = line.split(m_delimeter_str);
        std::list<std::string> asd ;
         //l_dataList_v.push_back(l_words.toVector());
    }

    file.close();

    return l_dataList_v;
}*/

std::vector<std::vector<std::string> > CSVReader::getData()
{
    std::ifstream file(m_fileName_str.toStdString());
    std::vector<std::vector<std::string> > l_dataList_v;
    l_dataList_v.clear();

    std::string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(m_delimeter_str.toStdString()));
        l_dataList_v.push_back(vec);
    }
    // Close the File
    file.close();

    return l_dataList_v;
}
