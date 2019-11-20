#include "cudatconsole.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QString l_dataBasePath = argv[1];
  QString l_delimeter = argv[2];
  QString l_selectRule = argv[3];

  CuDatConsole query(l_dataBasePath, l_delimeter, l_selectRule);
  query.runQuery();

  return a.exec();
}
