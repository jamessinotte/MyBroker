#include "mybroker.h"
#include "ui_mybroker.h"
#include <iostream>
MyBroker::MyBroker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyBroker)
{
    ui->setupUi(this);
}

MyBroker::~MyBroker()
{
    delete ui;
}
