#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include "ui_signup.h"
#include "ui_login.h"
#include "database.h"
#include "functions.h"
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPushButton>




namespace Ui {
class MyBroker;
}

class Signup : public QWidget, public functions
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);


    void checkInfo(QLineEdit* signupUsername, QLineEdit* signupEmail, QLineEdit* signupPassword, QLineEdit* confirmPassword, QLineEdit* firstName, QLineEdit* lastName, QLabel* errorText);
    void errorHandle(std::string error);
    void sendInfo();

    ~Signup();
signals:
    void switchToLogin();

private:
    Ui::Signup *ui;
    Ui::Login *Loginui;
    QWidget *currentWidget;
    QString lastName;
    QString firstName;
    QString email;
    QString username;
    QString password;









};
#endif // SIGNUP_H
