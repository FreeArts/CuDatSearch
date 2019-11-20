#ifndef CUDATCONSOLE_H
#define CUDATCONSOLE_H

#include "csvreader.h"
#include "select.h"

#include <QDebug>
#include <QObject>
#include <QString>
#include <QVector>

class CuDatConsole {

public:
  CuDatConsole();
  CuDatConsole(QString f_dataBasePath, QString f_delimeter_str,
               QString f_SelectRule_str);
  ~CuDatConsole();

  void runQuery();

private:
  QString m_databaseFileName_str;
  QString m_delimeter_str;
  QString m_queryCommand_str;

  SELECT m_SelectProcess;

  QVector<QString> m_selectRule_v;
  QVector<QString> m_selectTargets_v;
  std::vector<std::string> m_selectRule_stdv;
  std::vector<std::string> m_selectTargets_stdv;

  // QVector<QVector<QString>> m_dataList_v;
  std::vector<std::vector<long>> m_dataList_v;
  std::vector<std::string> m_headerOfDataBase_v;

  void showDataList(const vector<vector<long>> &l_parallelResultValue_v);
  void characterAlignment(QString &f_targetString);

  void prepareQuery(QString f_SelectRule_str);
  void vectorConvert(const QVector<QString> &f_selectRule_v,
                     const QVector<QString> &f_selectTargets_v);

  void loadDatabase(QString f_dataBasePath);
};

#endif // CUDATCONSOLE_H
