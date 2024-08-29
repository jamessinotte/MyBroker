#ifndef INVESTMENT_H
#define INVESTMENT_H
#include <QWidget>
#include <cpr/cpr.h>
#include "functions.h"
#include "datahandler.h"
#include <QCoreApplication>
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <variant>
#include <sstream>
#include <cmath>
#include "database.h"
#include <iostream>
#include <map>



class investment
{
public:

    investment(QString &stock);
    QString getSingleProfit(double investedMoney, double shares, std::string stock);
    QString getSingleInflationProfit(std::string date, double investedMoney, double shares);
    QString getTotalProfit();
    QString getTotalInflationProfit();
    std::string getRealTimeQuote(const std::string &stock);
    QString name;
    std::map<int, std::array<QString,3>> investmentMap;
    std::map<std::string, std::string> stockQuote;
    int totalShares;
    double totalProfit;
    double totalProfitInflation;
    std::map<std::string, double> profitmap;
    double currentPrice;
    std::string stockdata;
    void addInvestment(int id, QString price, QString shares, QString date);
    std::string priceString;



private:
    database& db = database::getInstance();
    int userid;


};

#endif // INVESTMENT_H
