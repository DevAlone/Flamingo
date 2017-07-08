#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T16:49:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Flamingo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    course.cpp \
    module.cpp \
    moduleitem.cpp \
    lesson.cpp \
    question.cpp \
    submodule.cpp \
    parser/coursesparser.cpp \
    exceptions/parserexception.cpp \
    exceptions/parseerrorexception.cpp \
    parser/modulesparser.cpp \
    exceptions/coursesparserexception.cpp \
    exceptions/modulesparserexception.cpp \
    parser/lessonsparser.cpp \
    exceptions/lessonsparserexception.cpp \
    parser/parser.cpp \
    parser/parserlogger.cpp \
    parser/logentry.cpp \
    parser/coursesparserlogentry.cpp \
    parser/modulesparserlogentry.cpp \
    parser/parserlogentry.cpp \
    parser/lessonsparserlogentry.cpp

HEADERS += \
        mainwindow.h \
    course.h \
    module.h \
    moduleitem.h \
    lesson.h \
    question.h \
    submodule.h \
    parser/coursesparser.h \
    exceptions/parserexception.h \
    exceptions/parseerrorexception.h \
    parser/modulesparser.h \
    exceptions/coursesparserexception.h \
    exceptions/modulesparserexception.h \
    parser/lessonsparser.h \
    exceptions/lessonsparserexception.h \
    parser/parser.h \
    parser/parserlogger.h \
    parser/logentry.h \
    parser/include.h \
    parser/coursesparserlogentry.h \
    parser/modulesparserlogentry.h \
    parser/parserlogentry.h \
    parser/lessonsparserlogentry.h

FORMS += \
        mainwindow.ui

CONFIG += c++14
