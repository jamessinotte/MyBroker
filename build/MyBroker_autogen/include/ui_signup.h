/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Signup
{
public:
    QPushButton *loginPageButton;
    QPushButton *SignupButton;
    QLabel *errorText;
    QLineEdit *signupPassword;
    QLineEdit *signupUsername;
    QLineEdit *signupEmail;
    QLineEdit *confirmPassword;
    QLineEdit *firstName;
    QLineEdit *lastName;

    void setupUi(QWidget *Signup)
    {
        if (Signup->objectName().isEmpty())
            Signup->setObjectName("Signup");
        Signup->resize(1920, 1080);
        loginPageButton = new QPushButton(Signup);
        loginPageButton->setObjectName("loginPageButton");
        loginPageButton->setGeometry(QRect(480, 590, 89, 25));
        SignupButton = new QPushButton(Signup);
        SignupButton->setObjectName("SignupButton");
        SignupButton->setGeometry(QRect(740, 690, 89, 25));
        errorText = new QLabel(Signup);
        errorText->setObjectName("errorText");
        errorText->setGeometry(QRect(760, 660, 67, 17));
        signupPassword = new QLineEdit(Signup);
        signupPassword->setObjectName("signupPassword");
        signupPassword->setGeometry(QRect(710, 300, 113, 25));
        signupUsername = new QLineEdit(Signup);
        signupUsername->setObjectName("signupUsername");
        signupUsername->setGeometry(QRect(710, 200, 113, 25));
        signupEmail = new QLineEdit(Signup);
        signupEmail->setObjectName("signupEmail");
        signupEmail->setGeometry(QRect(720, 120, 113, 25));
        confirmPassword = new QLineEdit(Signup);
        confirmPassword->setObjectName("confirmPassword");
        confirmPassword->setGeometry(QRect(700, 390, 113, 25));
        firstName = new QLineEdit(Signup);
        firstName->setObjectName("firstName");
        firstName->setGeometry(QRect(710, 490, 113, 25));
        lastName = new QLineEdit(Signup);
        lastName->setObjectName("lastName");
        lastName->setGeometry(QRect(710, 560, 113, 25));

        retranslateUi(Signup);

        QMetaObject::connectSlotsByName(Signup);
    } // setupUi

    void retranslateUi(QWidget *Signup)
    {
        Signup->setWindowTitle(QCoreApplication::translate("Signup", "Form", nullptr));
        loginPageButton->setText(QCoreApplication::translate("Signup", "Login", nullptr));
        SignupButton->setText(QCoreApplication::translate("Signup", "Signup", nullptr));
        errorText->setText(QCoreApplication::translate("Signup", "TextLabel", nullptr));
        signupPassword->setText(QCoreApplication::translate("Signup", "password", nullptr));
        signupUsername->setText(QCoreApplication::translate("Signup", "username", nullptr));
        signupEmail->setText(QCoreApplication::translate("Signup", "email", nullptr));
        confirmPassword->setText(QCoreApplication::translate("Signup", "confirm Password", nullptr));
        firstName->setText(QCoreApplication::translate("Signup", "firstName", nullptr));
        lastName->setText(QCoreApplication::translate("Signup", "lastName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Signup: public Ui_Signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
