#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>

#include "csvreader.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
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
    QVector<QString> m_selectRule_v;

    QVector<QVector<QString>> m_dataList_v;

    void showDataList();
    void characterAlignment(QString &l_targetString);

};

#endif // MAINWINDOW_H
