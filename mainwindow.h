#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>

#include "csvreader.h"
#include "select.h"

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_searchButton_clicked();

  void on_loadDatabaseButton_clicked();

  void on_runQueryButton_clicked();

private:
  Ui::MainWindow *ui;
  QString m_databaseFileName_str;
  QString m_delimeter_str;
  QString m_queryCommand_str;

  SELECT m_SelectProcess;

  QVector<QString> m_selectRule_v;
  QVector<QString> m_selectTargets_v;
  std::vector<std::string> m_selectRule_stdv;
  std::vector<std::string> m_selectTargets_stdv;

  // QVector<QVector<QString>> m_dataList_v;
  std::vector<std::vector<long int>> m_dataList_v;
  std::vector<std::string> m_headerOfDataBase_v;

  void showDataList();
  void characterAlignment(QString &f_targetString);

  void prepareQuery();
  void vectorConvert(const QVector<QString> &f_selectRule_v,
                     const QVector<QString> &f_selectTargets_v);

  void drawResults(vector<vector<long>> f_parallelResultValue_v);
};

#endif // MAINWINDOW_H
