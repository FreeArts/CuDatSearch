#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_delimeter_str = ";";
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_searchButton_clicked() {
  QFileDialog l_fileDialog(this);
  QStringList l_databaseFilePath;

  l_fileDialog.exec();
  l_databaseFilePath = l_fileDialog.selectedFiles();

  ui->lineEdit->clear();
  m_databaseFileName_str = l_databaseFilePath.back();
  ui->lineEdit->setText(m_databaseFileName_str);
}

void MainWindow::on_loadDatabaseButton_clicked() {
  m_delimeter_str = ui->delimeterBox->currentText();
  CSVReader *reader = new CSVReader(m_databaseFileName_str, m_delimeter_str);

  reader->readData();

  m_dataList_v = reader->getDataBase();
  m_headerOfDataBase_v = reader->getHeaderOfDatabse();

  m_SelectProcess.loadDatabase(m_dataList_v, m_headerOfDataBase_v);

  //----------D-R-A-W-T-A-B-L-E---------
  ui->tableWidget->setRowCount(static_cast<int>(m_dataList_v.size()));
  ui->tableWidget->setColumnCount(
      static_cast<int>(m_headerOfDataBase_v.size()));
  // For Qt part test. Original showDataList is on Cuda side!
  // showDataList();

  delete reader;
}

void MainWindow::showDataList() {
  /*for(QVector<QString> vec : m_dataList_v)
      {
          for(QString vector_member : vec)
          {
              qDebug() <<vector_member << ";";
          }
          qDebug() << "\n";
      }
*/
  // ui->tableWidget->setShowGrid(true);
  // ui->tableWidget->setRowCount(10);
  // ui->tableWidget->setColumnCount(5);
  // ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Hello"));
}

void MainWindow::characterAlignment(QString &f_targetString) {
  f_targetString.remove("\"");

  f_targetString.replace(" =", "=");
  f_targetString.replace("= ", "=");

  f_targetString.replace(" ,", ",");
  f_targetString.replace(", ", ",");
}

void MainWindow::prepareQuery() {
  const unsigned int lc_beforeWherePart = 0;
  const unsigned int lc_afterWherePart = 1;
  const unsigned int lc_TargetPart = 1;

  // SELECT name,brand where date="2010" & sex="men" | brand="ktm"
  // SELECT name,brand where date="2010" & sex="1" | brand="3"
  QString l_tmpSelectRule_str = ui->querytEdit->toPlainText();
  // QString l_queryCommand; Dead code?

  QStringList l_ruleWherePartDivide;
  QStringList l_selectRuleParts;
  QStringList l_selectTargetsParts;
  QStringList l_selectTargets;

  characterAlignment(l_tmpSelectRule_str);

  // Part0: SELECT name,brand where
  // Part1:date="2010" & sex="men" | brand="ktm"
  l_ruleWherePartDivide =
      l_tmpSelectRule_str.split("where", QString::SkipEmptyParts);

  //(Part0:date="2010") (Part1:&) (Part2:sex="men") (Part3:|)
  //(Part4:brand="ktm")
  l_selectRuleParts = l_ruleWherePartDivide.at(lc_afterWherePart)
                          .split(" ", QString::SkipEmptyParts);

  //(Part0:SELECT) (Part1:name,brand)
  l_selectTargetsParts = l_ruleWherePartDivide.at(lc_beforeWherePart)
                             .split(" ", QString::SkipEmptyParts);
  //(Part0:name) (Part1:brand)
  l_selectTargets = l_selectTargetsParts.at(lc_TargetPart)
                        .split(",", QString::SkipEmptyParts);

  m_selectTargets_v = l_selectTargets.toVector();
  m_selectRule_v = l_selectRuleParts.toVector();
}

void MainWindow::vectorConvert(const QVector<QString> &f_selectRule_v,
                               const QVector<QString> &f_selectTargets_v) {
  for (QString l_ruleMember_str : f_selectRule_v) {
    m_selectRule_stdv.push_back(l_ruleMember_str.toStdString());
  }

  for (QString l_targetMember_str : f_selectTargets_v) {
    m_selectTargets_stdv.push_back(l_targetMember_str.toStdString());
  }
}

void MainWindow::drawResults(vector<vector<long int>> f_parallelResultValue_v) {

  int l_row_i = 0;
  int l_column_i = 0;

  for (vector<long int> currentLine : f_parallelResultValue_v) {
    l_column_i = 0;
    for (long int currentCell : currentLine) {
      ui->tableWidget->setItem(
          l_row_i, l_column_i,
          new QTableWidgetItem(QString::number(currentCell)));
      l_column_i++;
    }
    l_row_i++;
  }
}

void MainWindow::on_runQueryButton_clicked() {
  // Example query
  // SELECT name,brand where date=2010 & sex=1 | brand=3

  // init
  vector<vector<long int>> l_serialResultValue_v;
  vector<vector<long int>> l_parallelResultValue_v;
  l_serialResultValue_v.clear();
  l_parallelResultValue_v.clear();

  prepareQuery();
  vectorConvert(m_selectRule_v, m_selectTargets_v);

  // Serial method:
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  l_serialResultValue_v = m_SelectProcess.getQueryResult();

  //---------------------------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------------------
  drawResults(l_parallelResultValue_v);
  // m_selectRule_stdv.clear();
}
