#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QVector>
#include <QtTest/QtTest>

#include "csvreader.h"
#include "select.h"

class TestCuDatBase : public QObject {
  Q_OBJECT

  enum class testCases;
  testCases m_testSituation_e;
private slots:
  // -- setup/cleanup --
  void loadCSV(QString f_CSVpath_str);
  void simSelectRule(testCases f_testSitutation_ui);

  void simSelectRuleV2(testCases f_testSitutation_ui);

  void testSelectSimple();

  void testSelectComplex();

  unsigned int
  checkGoodResultNumbers(vector<vector<long>> f_serialResultValue_v);

private:
  QString m_databaseFileName_str;
  QString m_delimeter_str;
  QString m_queryCommand_str;

  SELECT m_SelectProcess;

  QVector<QString> m_selectTargets_v;
  std::vector<std::string> m_selectRule_stdv;
  std::vector<std::string> m_selectTargets_stdv;

  // QVector<QVector<QString>> m_dataList_v;
  std::vector<std::vector<long int>> m_dataList_v;
  std::vector<std::string> m_headerOfDataBase_v;

  vector<vector<long int>> m_goodResult_v;

  unsigned int m_goodResultNumber_ui;
};

#endif // MAINWINDOW_H
