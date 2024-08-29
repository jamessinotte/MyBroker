
#include <QApplication>
#include <iostream>
#include "uimanager.h"
#include "database.h"
#include "loadenv.h";
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loadenv::loadEnvFile("../../info.env");
    database& db = database::getInstance();
    db.connect();
    UiManager w;
    w.show();
    return a.exec();
}
