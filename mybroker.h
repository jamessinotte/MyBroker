#ifndef MYBROKER_H
#define MYBROKER_H

#include <QMainWindow>

namespace Ui {
class MyBroker;
class Login;
class Homepage;
class Signup;
}

class MyBroker : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyBroker(QWidget *parent = nullptr);
    ~MyBroker();

private:
    Ui::MyBroker *ui;
};

#endif // MYBROKER_H
