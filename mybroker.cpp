#include "mybroker.h"
#include "ui_mybroker.h"

#include <iostream>




MyBroker::MyBroker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyBroker),
      Signupui(nullptr),
      Loginui(nullptr),
      currentWidget(nullptr)


{
    ui->setupUi(this);
    connect(ui->loginButton,&QPushButton::clicked,this, [=](){
        SwitchUI("Login");
    });
    connect(ui->brokerSignUp,&QPushButton::clicked,this, [=](){
        SwitchUI("Signup");
    });
    Signupui = new Signup(this);
    Loginui = new Login(this);
    Loginui -> hide();
    Signupui -> hide();


}

MyBroker::~MyBroker()
{
    delete ui;
}

void MyBroker::SwitchUI(const QString &newUI) {
    std::cout << "Switch" << std::endl;

    if (newUI == "Signup") {
        Signupui -> show();
        currentWidget = Signupui;
    }
    else if (newUI == "Login") {
        currentWidget = Loginui;
    }
    setCentralWidget(currentWidget);
    currentWidget -> show();






}


bool MyBroker::eventFilter(QObject *obj, QEvent *event) {
    
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(obj);
    if (lineEdit) {
        if (event->type() == QEvent::FocusIn) {
            lineEdit->clear(); // Clear text when the field gains focus
        } else if (event->type() == QEvent::FocusOut) {
            if (lineEdit->text().isEmpty()) {
                lineEdit->clear(); // Clear the placeholder text if the field is empty
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
