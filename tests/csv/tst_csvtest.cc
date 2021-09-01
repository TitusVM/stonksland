#include <QtTest>

#include "csv.h"
Q_DECLARE_METATYPE(std::vector<std::vector<std::string>>);

class CsvTest : public QObject
{
  Q_OBJECT

public:
  CsvTest();
  ~CsvTest();

private slots:
  void test_reading_data();
  void test_reading();
};

CsvTest::CsvTest()
{
}

CsvTest::~CsvTest()
{
}

void CsvTest::test_reading_data()
{
  QTest::addColumn<QString>("filename");
  QTest::addColumn<QString>("content");
  QTest::addColumn<std::vector<std::vector<std::string>>>("result");

  QTest::addRow("empty")
      << "empty.csv"
      << ""
      << std::vector<std::vector<std::string>>();

  QTest::addRow("simple")
      << "simple.csv"
      << "country,currency,symbol,iso\r\nSwitzerland,Swiss franc,CHF,CHF"
      << std::vector<std::vector<std::string>> {
         std::vector<std::string> { "country", "currency", "symbol", "iso" },
         std::vector<std::string> { "Switzerland", "Swiss franc", "CHF", "CHF" }
  };

  QTest::addRow("special chars")
      << "special_chars.csv"
      << "country,currency,symbol,iso\r\nSri Lanka,Sri Lankan rupee,\"Rs, රු  or  ரூ\",LKR\r\nChina,Chinese yuan,¥ or 元,CNY\r\n"
      << std::vector<std::vector<std::string>> {
         std::vector<std::string> { "country", "currency", "symbol", "iso" },
         std::vector<std::string> { "Sri Lanka", "Sri Lankan rupee", "Rs, රු  or  ரூ", "LKR" },
         std::vector<std::string> { "China", "Chinese yuan", "¥ or 元", "CNY" }
  };
}

void CsvTest::test_reading() {
  QFETCH(QString, filename);
  QFETCH(QString, content);
  QFETCH(std::vector<std::vector<std::string>>, result);

  QFile::remove(filename);
  if (QFile::exists(filename)) {
    QSKIP("Couldn't remove the old test file before the test");
  }

  QFile fileWrite(filename);
  fileWrite.open(QFile::WriteOnly);
  fileWrite.write(content.toStdString().c_str());
  fileWrite.close();

  if (!QFile::exists(filename)) {
    QSKIP("Couldn't create the test file");
  }

  QFile fileRead(filename);
  fileRead.open(QFile::ReadOnly);
  QCOMPARE(readCSV(fileRead), result);
}

QTEST_MAIN(CsvTest)
#include "tst_csvtest.moc"
