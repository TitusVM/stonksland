QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testcache.cc \
  ../../StonksLand/cache.cc

INCLUDEPATH += ../../StonksLand
