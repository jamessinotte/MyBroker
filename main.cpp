#include "mybroker.h"
#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    std::cout << "started" << std::endl;
    QApplication a(argc, argv);
    MyBroker w;
    w.show();
    return a.exec();
}
