#include "loadenv.h"


void loadenv::loadEnvFile(const QString &filePath) {
    QFile file(filePath);
    if (!QFile::exists(filePath)) {
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty() || line.startsWith('#')) continue;

        QStringList parts = line.split('=', Qt::SkipEmptyParts);
        if (parts.size() == 2) {
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            qputenv(key.toUtf8(), value.toUtf8());
        }
    }
}
