TEMPLATE = app
CONFIG += c++17
QT += widgets
QT += core sql

SOURCES += main.cpp \
           signup.cpp

HEADERS += signup.h

FORMS += signup.ui

INCLUDEPATH += /home/james/MyBroker/mongo-cxx-driver/install/include/bsoncxx/v_noabi
LIBS += -L/home/james/MyBroker/mongo-cxx-driver/install/lib -lmongocxx
