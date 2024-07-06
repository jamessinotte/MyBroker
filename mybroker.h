#ifndef MYBROKER_H
#define MYBROKER_H
#include "signup.h"
#include "login.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MyBroker;
class Signup;
class Login;
}

QT_END_NAMESPACE

class MyBroker : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyBroker(QWidget *parent = nullptr);
    ~MyBroker();

public:

    bool eventFilter(QObject *obj, QEvent *event);
    void SwitchUI(const QString &newUI);




private:
    Ui::MyBroker *ui;
    Signup *Signupui;  // Changed to Signup pointer
    Login *Loginui;
    QWidget *currentWidget;

};
#endif // MYBROKER_H
