#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "login.h"
#include "signup.h"
#include "homepage.h"
#include "ui_mybroker.h"
#include "ui_signup.h"
#include "ui_login.h"
#include <iostream>

class Login;
class Signup;
class Homepage;
namespace Ui {
class MyBroker;
}
class UiManager : public QWidget
{
    Q_OBJECT

public:
    explicit UiManager(QWidget *parent = nullptr);
    ~UiManager();

public slots:
    void switchToLogin();
    void switchToSignup();
    void switchToHomepage();




private:

    QStackedWidget *stackedWidget;
    Login *loginUi;
    Signup *signupUi;
    Homepage *homepageUi;
    Ui::MyBroker *ui;

};

#endif // UIMANAGER_H
