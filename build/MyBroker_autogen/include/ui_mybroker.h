/********************************************************************************
** Form generated from reading UI file 'mybroker.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYBROKER_H
#define UI_MYBROKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyBroker
{
public:
    QWidget *centralwidget;
    QPushButton *loginButton;
    QPushButton *brokerSignUp;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MyBroker)
    {
        if (MyBroker->objectName().isEmpty())
            MyBroker->setObjectName("MyBroker");
        MyBroker->resize(1920, 1080);
        centralwidget = new QWidget(MyBroker);
        centralwidget->setObjectName("centralwidget");
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(280, 260, 89, 25));
        brokerSignUp = new QPushButton(centralwidget);
        brokerSignUp->setObjectName("brokerSignUp");
        brokerSignUp->setGeometry(QRect(620, 290, 89, 25));
        MyBroker->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyBroker);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 22));
        MyBroker->setMenuBar(menubar);
        statusbar = new QStatusBar(MyBroker);
        statusbar->setObjectName("statusbar");
        MyBroker->setStatusBar(statusbar);

        retranslateUi(MyBroker);

        QMetaObject::connectSlotsByName(MyBroker);
    } // setupUi

    void retranslateUi(QMainWindow *MyBroker)
    {
        MyBroker->setWindowTitle(QCoreApplication::translate("MyBroker", "MyBroker", nullptr));
        loginButton->setText(QCoreApplication::translate("MyBroker", "Login", nullptr));
        brokerSignUp->setText(QCoreApplication::translate("MyBroker", "Signup", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyBroker: public Ui_MyBroker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYBROKER_H
