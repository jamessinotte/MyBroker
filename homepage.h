#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "database.h"
#include "functions.h"
#include "investment.h"
#include <iostream>
#include <memory>
#include <QPushButton>
#include <qboxlayout.h>
#include <QRandomGenerator>
#include <QScrollBar>
#include <QScrollArea>
#include <QLabel>
#include <QFormLayout>
#include <QtConcurrent/QtConcurrent>
#include <QThread>


namespace Ui {
class Homepage;
}

class Homepage : public QWidget, public functions
{
    Q_OBJECT

public:
    explicit Homepage(QWidget *parent = nullptr);
    ~Homepage();
    void displayStocks();
    std::map<std::string, std::array<std::string,2>> deleteMap;
    QString generateRandomKey(int length);
    std::vector<std::string> stockList;
    int row;
    int col = 0;
    std::map<QString, std::unique_ptr<investment>> stocks;
    void updateProfitLabels(const QString &stockName);
    QVBoxLayout* stockColumns[3];


public slots:
    void handleDeleteButton(QString QKey, QString stockName);
    void addStock();



private:
    Ui::Homepage *ui;
    QWidget *containerWidget;
    QVBoxLayout *stocksLayout;
    database& db = database::getInstance();

};

#endif // HOMEPAGE_H
