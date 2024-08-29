#include "functions.h"
#include <iostream>
functions::functions() {


}



bool functions::eventFilter(QObject *obj, QEvent *event) {

    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(obj);
    if (lineEdit) {
        if (event->type() == QEvent::FocusIn) {
            lineEdit->clear(); //
        } else if (event->type() == QEvent::FocusOut) {
            if (lineEdit->text().isEmpty()) {
                lineEdit->clear();
            }
        }
    }
    return window->eventFilter(obj, event);
}
QString functions::getText(QObject *parent, std::string type) {

    QString qType = QString::fromStdString(type);
    QLineEdit *lineEdit = parent->findChild<QLineEdit*>(qType);

    if (!lineEdit) {

        return QString();
    }


    QString text = lineEdit->text();


    return text;
}

