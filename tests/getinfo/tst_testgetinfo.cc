#include <QtTest>

#include "getinfo.h"

class TestGetInfo : public QObject
{
  Q_OBJECT

public:
  TestGetInfo();
  ~TestGetInfo();

private slots:
  void initTestCase();

  void test_findCountry_byName();
  void test_findCountries_byCurrency();
  void test_findCurrency_byName();
  void test_getCurrencyList();
};

TestGetInfo::TestGetInfo()
{
}

TestGetInfo::~TestGetInfo()
{
}

void TestGetInfo::initTestCase() {
  QFile::remove("file.csv");
  if (QFile::exists("file.csv")) {
    QSKIP("Couldn't remove the old test file before the test");
  }

  QFile file("file.csv");
  file.open(QFile::WriteOnly);
  file.write("country,currency,symbol,iso\r\nArmenia,Armenian dram,֏,AMD\r\nAruba,Aruban florin,ƒ,AWG\r\nAustralia,Australian dollar,$,AUD\r\nAustria,Euro,€,EUR\r\nAzerbaijan,Azerbaijani manat,₼,AZN\r\nFrance,Euro,€,EUR");
  file.close();

  if (!QFile::exists("file.csv")) {
    QSKIP("Couldn't create the test file.");
  }
}

void TestGetInfo::test_findCountry_byName() {
  GetInfo info("file.csv");

  Country c = info.findCountry("Armenia");
  QCOMPARE(c.getName(), "Armenia");
  QCOMPARE(c.getCurrency().getISO(), "AMD");

  c = info.findCountry("Austria");
  QCOMPARE(c.getName(), "Austria");
  QCOMPARE(c.getCurrency().getISO(), "EUR");
}

void TestGetInfo::test_findCountries_byCurrency() {
  GetInfo info("file.csv");

  Currency curr("Euro", "€", "EUR");
  std::vector<Country> countries = info.findCountries(curr);
  QCOMPARE(countries.size(), 2);
  QCOMPARE(countries[0].getName(), "Austria");
  QCOMPARE(countries[0].getCurrency(), curr);
  QCOMPARE(countries[1].getName(), "France");
  QCOMPARE(countries[1].getCurrency(), curr);
}

void TestGetInfo::test_findCurrency_byName() {
  GetInfo info("file.csv");
  Currency curr = info.findCurrency("Aruban florin");
  QCOMPARE(curr.getName(), "Aruban florin");
  QCOMPARE(curr.getSymbol(), "ƒ");
  QCOMPARE(curr.getISO(), "AWG");
}

void TestGetInfo::test_getCurrencyList() {
  GetInfo info("file.csv");
  std::vector<Currency> currencies = info.getCurrencyList();
  QCOMPARE(currencies.size(), 5);
  QCOMPARE(currencies[0], Currency("Armenian dram", "֏", "AMD"));
  QCOMPARE(currencies[1], Currency("Aruban florin", "ƒ", "AWG"));
  QCOMPARE(currencies[2], Currency("Australian dollar", "$", "AUD"));
  QCOMPARE(currencies[3], Currency("Euro", "€", "EUR"));
  QCOMPARE(currencies[4], Currency("Azerbaijani manat", "₼", "AZN"));
}

QTEST_APPLESS_MAIN(TestGetInfo)

#include "tst_testgetinfo.moc"
