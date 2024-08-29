#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "database.h"
#include "ui_login.h"
#include "functions.h"
#include "uimanager.h"
#include "mybroker.h"
#include "database.h"
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>




namespace Ui {
class Login;
}

class Login : public QWidget, public functions
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool signin();
    void error();

signals:
    void switchToSignup();
    void switchToHomepage();
private slots:
    void onSignupButtonClicked();


private:
    Ui::Login *ui;
    database& db = database::getInstance();


};

#endif // LOGIN_H
