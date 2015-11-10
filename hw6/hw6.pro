######################################################################
# Automatically generated by qmake (2.01a) Mon Nov 2 16:58:26 2015
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += markdownparser.h \
           msort.h \
           myset.h \
           pageparser.h \
           search_window.h \
           searcheng.h \
           util.h \
           webpage.h \
           webpage_window.h \
           config.h
SOURCES += markdownparser.cpp \
           pageparser.cpp \
           search.cpp \
           search_window.cpp \
           searcheng.cpp \
           util.cpp \
           webpage.cpp \
           webpage_window.cpp \
           config.cpp


CONFIG += debug               # enables debugging (like the -g flag)
TARGET = search               # sets output executable name to search
QMAKE_CXXFLAGS += -std=c++11  # enable C++11 libraries
SOURCES -= msort_test.cpp # Don't compile certain test files as part of the search application
