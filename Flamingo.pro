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
    submodule.cpp \
    parser/coursesparser.cpp \
    parser/modulesparser.cpp \
    parser/lessonsparser.cpp \
    parser/parser.cpp \
    parser/logger/parserlogger.cpp \
    parser/logger/logentry.cpp \
    parser/logger/coursesparserlogentry.cpp \
    parser/logger/modulesparserlogentry.cpp \
    parser/logger/parserlogentry.cpp \
    parser/logger/lessonsparserlogentry.cpp \
    parser/pagesparser.cpp \
    page.cpp \
    parser/logger/pagesparserlogentry.cpp \
    answer.cpp \
    parser/answersparser.cpp \
    textpage.cpp \
    exceptions/pagecreatingerror.cpp \
    htmlpage.cpp \
    parser/logger/answersparserlogentry.cpp \
    exceptions/answercreatingerror.cpp \
    rightanswers.cpp

HEADERS += \
        mainwindow.h \
    course.h \
    module.h \
    moduleitem.h \
    lesson.h \
    submodule.h \
    parser/coursesparser.h \
    parser/modulesparser.h \
    parser/lessonsparser.h \
    parser/parser.h \
    parser/logger/parserlogger.h \
    parser/logger/logentry.h \
    parser/include.h \
    parser/logger/coursesparserlogentry.h \
    parser/logger/modulesparserlogentry.h \
    parser/logger/parserlogentry.h \
    parser/logger/lessonsparserlogentry.h \
    nullable.hpp \
    parser/pagesparser.h \
    page.h \
    parser/logger/pagesparserlogentry.h \
    answer.h \
    parser/answersparser.h \
    textpage.h \
    exceptions/pagecreatingerror.h \
    htmlpage.h \
    parser/logger/answersparserlogentry.h \
    exceptions/answercreatingerror.h \
    rightanswers.h

FORMS += \
        mainwindow.ui

CONFIG += c++14
