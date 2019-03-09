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


    l_fileDialog.exec();
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

    showDataList();

    delete reader;
}

void MainWindow::showDataList()
{
    for(QVector<QString> vec : m_dataList_v)
        {
            for(QString vector_member : vec)
            {
                qDebug() <<vector_member << ";";
            }
            qDebug() << "\n";
        }

    //ui->tableWidget->setShowGrid(true);
    //ui->tableWidget->setRowCount(10);
    //ui->tableWidget->setColumnCount(5);
    //ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Hello"));

}

void MainWindow::characterAlignment(QString &l_targetString)
{
    l_targetString.remove("\"");

    l_targetString.replace(" =","=");
    l_targetString.replace("= ","=");


    l_targetString.replace(" ,",",");
    l_targetString.replace(", ",",");
}

void MainWindow::on_runQueryButton_clicked()
{
    const unsigned int lc_afterWherePart=1;

    //SELECT name,brand where date="2010" & sex="men" | brand="ktm"
    QString l_tmpSelectRule = ui->querytEdit->toPlainText();
    QStringList l_ruleWherePartDivide;
    QStringList l_selectRuleParts;

    characterAlignment(l_tmpSelectRule);

    l_ruleWherePartDivide = l_tmpSelectRule.split("where",QString::SkipEmptyParts);
    l_selectRuleParts = l_ruleWherePartDivide.at(lc_afterWherePart).split(" ",QString::SkipEmptyParts);

    m_selectRule_v = l_selectRuleParts.toVector();
}
