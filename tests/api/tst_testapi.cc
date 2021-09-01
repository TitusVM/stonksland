#include <QtTest>

#include "api.h"
typedef QMap<QString, double> RatesType; // templates don't work with the QFETCH macro

class TestApi : public QObject
{
  Q_OBJECT

public:
  TestApi();
  ~TestApi();

private slots:
  void test_extractRates_data();
  void test_extractRates();

};

TestApi::TestApi()
{
}

TestApi::~TestApi()
{
}

void TestApi::test_extractRates_data()
{
  QTest::addColumn<QString>("js");
  QTest::addColumn<QMap<QString, double>>("result");

  QTest::addRow("empty string") << "" << QMap<QString, double>();
  QTest::addRow("empty js") << "{}" << QMap<QString, double>();
  QTest::addRow("good js")
      << "{\"rates\":{\"AED\":4.333642,\"AFN\":104.022543,\"ALL\":121.955052,\"AMD\":583.225046}}"
      << QMap<QString, double> {
    {"AED", 4.333642},
    {"AFN", 104.022543},
    {"ALL", 121.955052},
    {"AMD", 583.225046}
  };
}

void TestApi::test_extractRates()
{
  QFETCH(QString, js);
  QFETCH(RatesType, result);

  QCOMPARE(Api::extractRates(js), result);
}

QTEST_MAIN(TestApi)
#include "tst_testapi.moc"
