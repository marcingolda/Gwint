#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T22:03:54
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += network

TARGET = NewGwint
TEMPLATE = app


HEADERS += src/gracz.h \
           src/karta.h \
           src/klient.h \
           src/koniec.h \
           src/random.h \
           src/server.h \
           src/start.h \
           src/talia.h \
           src/thread.h
FORMS +=   ui/koniec.ui \
           ui/plansza.ui \
           ui/start.ui
SOURCES += src/gracz.cpp \
           src/karta.cpp \
           src/klient.cpp \
           src/koniec.cpp \
           src/main.cpp \
           src/random.cpp \
           src/server.cpp \
           src/start.cpp \
           src/talia.cpp \
           src/thread.cpp
RESOURCES += resources/cards.qrc

