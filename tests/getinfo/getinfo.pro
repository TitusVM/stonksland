QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testgetinfo.cc \
  ../../StonksLand/getinfo.cc \
  ../../StonksLand/currency.cc \
  ../../StonksLand/country.cc \
  ../../StonksLand/csv.cc

INCLUDEPATH += ../../StonksLand
