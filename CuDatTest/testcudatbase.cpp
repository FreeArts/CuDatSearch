#include "testcudatbase.h"

enum class TestCuDatBase::testCases {
  simpleTest,
  testCase2,
  testCase3,
  testCase4,
  testCase5,
  testCase6,
  testCase7
};

void TestCuDatBase::loadCSV(QString f_CSVpath_str) {

  m_delimeter_str = ";";
  m_databaseFileName_str = f_CSVpath_str;
  CSVReader *reader = new CSVReader(m_databaseFileName_str, m_delimeter_str);

  reader->readData();

  m_dataList_v.clear();
  m_headerOfDataBase_v.clear();

  m_dataList_v = reader->getDataBase();
  m_headerOfDataBase_v = reader->getHeaderOfDatabse();

  m_SelectProcess.loadDatabase(m_dataList_v, m_headerOfDataBase_v);

  delete reader;
}

void TestCuDatBase::simSelectRule(testCases f_testSitutation_e) {

  m_selectRule_stdv.clear();
  m_goodResult_v.clear();
  vector<long int> l_goodLine_v;

  switch (f_testSitutation_e) {

  case testCases::simpleTest: {
    m_selectRule_stdv.push_back("date=2010");
    m_selectRule_stdv.push_back("&");
    m_selectRule_stdv.push_back("sex=1");
    m_selectRule_stdv.push_back("|");
    m_selectRule_stdv.push_back("brand=3");

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2010);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(3);
    l_goodLine_v.push_back(13);

    m_goodResult_v.push_back(l_goodLine_v);
    m_goodResultNumber_ui = 1;

    break;
  }

  case testCases::testCase2: {
    m_selectRule_stdv.push_back("date=2010");
    m_selectRule_stdv.push_back("&");
    m_selectRule_stdv.push_back("sex=1");

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2010);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(3);
    l_goodLine_v.push_back(13);

    m_goodResult_v.push_back(l_goodLine_v);
    m_goodResultNumber_ui = 1;

    break;
  }

  case testCases::testCase3: {
    m_selectRule_stdv.push_back("date=2010");
    m_selectRule_stdv.push_back("&");
    m_selectRule_stdv.push_back("sex=2");

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2010);
    l_goodLine_v.push_back(2);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(11);

    m_goodResult_v.push_back(l_goodLine_v);
    m_goodResultNumber_ui = 1;

    break;
  }

  case testCases::testCase4: {
    m_selectRule_stdv.push_back("date=2009");
    m_selectRule_stdv.push_back("&");
    m_selectRule_stdv.push_back("sex=2");

    l_goodLine_v.clear();

    m_goodResult_v.push_back(l_goodLine_v);
    m_goodResultNumber_ui = 0;

    break;
  }

  case testCases::testCase5: {
    m_selectRule_stdv.push_back("date=2009");
    m_selectRule_stdv.push_back("&");
    m_selectRule_stdv.push_back("sex=1");

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2009);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(2);
    l_goodLine_v.push_back(12);

    m_goodResult_v.push_back(l_goodLine_v);
    m_goodResultNumber_ui = 1;

    break;
  }

  case testCases::testCase6: {
    m_selectRule_stdv.push_back("date=2010");

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2010);
    l_goodLine_v.push_back(2);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(11);

    m_goodResult_v.push_back(l_goodLine_v);

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2010);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(3);
    l_goodLine_v.push_back(13);

    m_goodResult_v.push_back(l_goodLine_v);

    m_goodResultNumber_ui = 2;

    break;
  }
  case testCases::testCase7: {
    m_selectRule_stdv.push_back("date=2009");
    m_selectRule_stdv.push_back("|");
    m_selectRule_stdv.push_back("sex=1");

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2009);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(2);
    l_goodLine_v.push_back(12);

    m_goodResult_v.push_back(l_goodLine_v);

    l_goodLine_v.clear();

    l_goodLine_v.push_back(2010);
    l_goodLine_v.push_back(1);
    l_goodLine_v.push_back(3);
    l_goodLine_v.push_back(13);

    m_goodResult_v.push_back(l_goodLine_v);

    m_goodResultNumber_ui = 2;
    break;
  }
  }
}

void TestCuDatBase::simSelectRuleV2(
    TestCuDatBase::testCases f_testSitutation_ui) {}

void TestCuDatBase::testSelectSimple() {

  vector<vector<long int>> l_serialResultValue_v;
  vector<vector<long int>> l_parallelResultValue_v;

  l_serialResultValue_v.clear();
  l_parallelResultValue_v.clear();

  //--Test--Software--Version--
  QString l_softwareVersion =
      QString::fromUtf8(m_SelectProcess.m_versionNumber_str.c_str());

  QVERIFY(l_softwareVersion == "v2.0 alpha");
  //---I-N-I-T-T-E-S-T----
  m_testSituation_e = testCases::simpleTest;
  loadCSV("/home/freeart/MscThesis/CuDatBase/cudatbase/src/CSV_dir/"
          "simple_test.csv");
  simSelectRule(m_testSituation_e);
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  //------------S-E-R-I-A-L------------
  l_serialResultValue_v = m_SelectProcess.getQueryResult();

  //------------P-A-R-A-L-L-E-L--------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------T-E-S-T-R-E-S-U-L-T--------------
  QCOMPARE(m_goodResultNumber_ui + 1,
           checkGoodResultNumbers(l_serialResultValue_v));
  QCOMPARE(m_goodResultNumber_ui,
           checkGoodResultNumbers(l_parallelResultValue_v));
  //------------------------------------------------
  //---I-N-I-T-T-E-S-T-----N-E-W----T-E-S-T----
  m_testSituation_e = testCases::testCase2;
  loadCSV("/home/freeart/MscThesis/CuDatBase/cudatbase/src/CSV_dir/"
          "simple_test.csv");
  simSelectRule(m_testSituation_e);
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  //------------P-A-R-A-L-L-E-L--------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------T-E-S-T-R-E-S-U-L-T--------------
  QCOMPARE(m_goodResultNumber_ui,
           checkGoodResultNumbers(l_parallelResultValue_v));
  //------------------------------------------------
  //---I-N-I-T-T-E-S-T-----N-E-W----T-E-S-T----
  m_testSituation_e = testCases::testCase3;
  loadCSV("/home/freeart/MscThesis/CuDatBase/cudatbase/src/CSV_dir/"
          "simple_test.csv");
  simSelectRule(m_testSituation_e);
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  //------------P-A-R-A-L-L-E-L--------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------T-E-S-T-R-E-S-U-L-T--------------
  QCOMPARE(m_goodResultNumber_ui,
           checkGoodResultNumbers(l_parallelResultValue_v));
  //------------------------------------------------
  //---I-N-I-T-T-E-S-T-----N-E-W----T-E-S-T----
  m_testSituation_e = testCases::testCase4;
  loadCSV("/home/freeart/MscThesis/CuDatBase/cudatbase/src/CSV_dir/"
          "simple_test.csv");
  simSelectRule(m_testSituation_e);
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  //------------P-A-R-A-L-L-E-L--------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------T-E-S-T-R-E-S-U-L-T--------------
  QCOMPARE(m_goodResultNumber_ui,
           checkGoodResultNumbers(l_parallelResultValue_v));
  //------------------------------------------------
  //---I-N-I-T-T-E-S-T-----N-E-W----T-E-S-T----
  m_testSituation_e = testCases::testCase5;
  loadCSV("/home/freeart/MscThesis/CuDatBase/cudatbase/src/CSV_dir/"
          "simple_test.csv");
  simSelectRule(m_testSituation_e);
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  //------------P-A-R-A-L-L-E-L--------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------T-E-S-T-R-E-S-U-L-T--------------
  QCOMPARE(m_goodResultNumber_ui,
           checkGoodResultNumbers(l_parallelResultValue_v));
  //------------------------------------------------
  //---I-N-I-T-T-E-S-T-----N-E-W----T-E-S-T----
  m_testSituation_e = testCases::testCase6;
  loadCSV("/home/freeart/MscThesis/CuDatBase/cudatbase/src/CSV_dir/"
          "simple_test.csv");
  simSelectRule(m_testSituation_e);
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  //------------P-A-R-A-L-L-E-L--------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------T-E-S-T-R-E-S-U-L-T--------------
  QCOMPARE(m_goodResultNumber_ui,
           checkGoodResultNumbers(l_parallelResultValue_v));
  //------------------------------------------------
  //---I-N-I-T-T-E-S-T-----N-E-W----T-E-S-T----
  m_testSituation_e = testCases::testCase7;
  loadCSV("/home/freeart/MscThesis/CuDatBase/cudatbase/src/CSV_dir/"
          "simple_test.csv");
  simSelectRule(m_testSituation_e);
  m_SelectProcess.readSelectRule(m_selectRule_stdv);
  m_SelectProcess.run();

  //------------P-A-R-A-L-L-E-L--------
  l_parallelResultValue_v = m_SelectProcess.parallelRun();
  //---------------T-E-S-T-R-E-S-U-L-T--------------
  QCOMPARE(m_goodResultNumber_ui,
           checkGoodResultNumbers(l_parallelResultValue_v));
  //------------------------------------------------
}

void TestCuDatBase::testSelectComplex() {}

unsigned int TestCuDatBase::checkGoodResultNumbers(
    vector<vector<long int>> f_serialResultValue_v) {

  unsigned int l_foundedGoodValues_ui = 0;

  for (vector<long int> currentLine : f_serialResultValue_v) {
    for (unsigned int l_itx_ui = 0; l_itx_ui < m_goodResult_v.size();
         l_itx_ui++) {
      if (currentLine == m_goodResult_v.at(l_itx_ui)) {
        l_foundedGoodValues_ui++;
      }
    }
  }

  return l_foundedGoodValues_ui;
}

QTEST_APPLESS_MAIN(TestCuDatBase)
