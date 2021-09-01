#include <QtTest>

#include "cache.h"

class TestCache : public QObject
{
  Q_OBJECT

public:
  TestCache();
  ~TestCache();

private slots:
  void test_createDir_data();
  void test_createDir();

  void test_readFile();

  void test_expiration();

  void test_writeNewCache();

  void test_rewriteOldCache();
};

TestCache::TestCache()
{
}

TestCache::~TestCache()
{

}

void TestCache::test_createDir_data() {
  QTest::addColumn<QString>("dir");

  QTest::newRow("one-level directory") << "cache";
  QTest::newRow("two-levels directory") << "cache2/test";
}

void TestCache::test_createDir()
{
  QFETCH(QString, dir);

  QDir(dir).removeRecursively();
  if (QDir(dir).exists())
    QSKIP("Couldn't remove the folder before the test");

  Cache cache(dir);
  QVERIFY(QDir(dir).exists());
}

void TestCache::test_readFile() {
  QDir("test_readFile").removeRecursively();

  if (QDir("test_readFile").exists()) {
    QSKIP("Couldn't remove the folder before the test");
  }

  QDir("test_readFile").mkdir(".");
  QFile f("test_readFile/file");
  f.open(QFile::WriteOnly);
  f.write("Test string.");
  f.close();

  if (!QFile("test_readFile/file").exists()) {
    QSKIP("Couldn't create the test file");
  }

  Cache cache("test_readFile");
  QVERIFY(cache.contains("file"));
  if (cache.contains("file")) {
    QCOMPARE(cache.get("file"), QString("Test string."));
  }
}

void TestCache::test_expiration() {
  QDir("test_expiration").removeRecursively();

  if (QDir("test_expiration").exists()) {
    QSKIP("Couldn't remove the folder before the test");
  }

  QDir("test_expiration").mkdir(".");
  QFile f("test_expiration/file");
  f.open(QFile::WriteOnly);
  f.write("Test string.");
  f.close();

  if (!QFile("test_expiration/file").exists()) {
    QSKIP("Couldn't create the test file");
  }

  QTest::qWait(3000);
  Cache cache("test_expiration", 2);

  QVERIFY(!cache.contains("file"));
}

void TestCache::test_writeNewCache() {
  QDir("test_writeNewCache").removeRecursively();
  if (QDir("test_writeNewCache").exists()) {
    QSKIP("Couldn't remove the folder before the test");
  }

  Cache cache("test_writeNewCache");
  cache.add("newfile", "File content");

  QVERIFY(cache.contains("newfile"));
  QCOMPARE(cache.get("newfile"), QString("File content"));

  QFile file("test_writeNewCache/newfile");
  file.open(QFile::ReadOnly);
  QString fileContent(file.readAll());
  QCOMPARE(fileContent, QString("File content"));
}

void TestCache::test_rewriteOldCache() {
  QDir("test_rewriteOldCache").removeRecursively();
  if (QDir("test_rewriteOldCache").exists()) {
    QSKIP("Couldn't remove the folder before the test");
  }

  QDir("test_rewriteOldCache").mkdir(".");
  QFile fileWrite("test_rewriteOldCache/file");
  fileWrite.open(QFile::WriteOnly);
  fileWrite.write("Cached data.");
  fileWrite.close();
  if (!QFile("test_rewriteOldCache").exists()) {
    QSKIP("Couldn't create the test file");
  }

  QTest::qSleep(3000);
  Cache cache("test_rewriteOldCache", 2);
  cache.add("file", "New cached data.");

  QVERIFY(cache.contains("file"));
  QCOMPARE(cache.get("file"), QString("New cached data."));

  QFile fileRead("test_rewriteOldCache/file");
  fileRead.open(QFile::ReadOnly);
  QString fileContent(fileRead.readAll());
  fileRead.close();
  QCOMPARE(fileContent, QString("New cached data."));
}

QTEST_MAIN(TestCache)
#include "tst_testcache.moc"
