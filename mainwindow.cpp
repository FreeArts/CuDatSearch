#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_delimeter_str = ";";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    QFileDialog l_fileDialog(this);
    QStringList l_databaseFilePath;

    if (l_fileDialog.exec())
        l_databaseFilePath = l_fileDialog.selectedFiles();

    ui->lineEdit->clear();
    m_databaseFileName_str = l_databaseFilePath.back();
    ui->lineEdit->setText(m_databaseFileName_str);
}

void MainWindow::on_loadDatabaseButton_clicked()
{
    m_delimeter_str = ui->delimeterBox->currentText();
    CSVReader *reader = new CSVReader(m_databaseFileName_str,m_delimeter_str);
    m_dataList_v =  reader->getData();

    for(QVector<QString> vec : m_dataList_v)
        {
            for(QString vector_member : vec)
            {
                qDebug() <<vector_member << ";";
            }
            qDebug() << "\n";
        }

    delete reader;
}
