#ifndef SIGNUP_H
#define SIGNUP_H

#include "qmainwindow.h"
#include <QWidget>
#include "ui_signup.h"
#include "ui_login.h"


namespace Ui {
class Signup;
class Login;
}

class Signup : public QWidget
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    std::string getText(QString type) const;

    void checkInfo();
    void errorHandle(std::string error);
    void sendInfo();


    ~Signup();

private:
    Ui::Signup *ui;
    Ui::Login *Loginui;
    QWidget *currentWidget;
    QString lastName;
    QString firstName;
    QString email;
    QString username;
    QString password;
signals:
    void switchUI(const QString &newUI);


};
#endif // SIGNUP_H
