#ifndef LOADENV_H
#define LOADENV_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <cstdlib>
#include <iostream>
class loadenv
{
public:
    loadenv();
    static void loadEnvFile(const QString &filePath);
};

#endif // LOADENV_H
