#include "investment.h"
#include <iostream>

investment::investment(QString &stock) {
    datahandler *dataHandler = new datahandler();
    stockdata = getRealTimeQuote(stock.toStdString());
    name = stock;
    stockQuote = dataHandler->parseObject(stockdata);
    priceString = stockQuote["price"];
    currentPrice = std::stoi(priceString);
    userid = db.userid;
    investmentMap = db.searchInvestments(name);

}



QString investment::getSingleProfit(double investedMoney, double shares, std::string stock){
    double currentValue = shares * currentPrice;
    currentValue *= 100;
    currentValue = std::round(currentValue);
    currentValue /= 100;
    return QString::number(currentValue);





}
QString investment::getTotalProfit() {
    totalProfit = 0;
    for (const auto& [key, array] : investmentMap) {
        double quantity = std::stod(array[1].toStdString());
        double value = std::stod(array[2].toStdString());
        QString profitString = (getSingleProfit(value,quantity,name.toStdString()));
            totalProfit += profitString.toDouble();
        }






    return QString::number(std::round(totalProfit * 100) / 100, 'f', 2);

}
void investment::addInvestment(int id, QString price, QString shares, QString date) {
    investmentMap[id] = {date,shares,price};
    db.addInvestment(name,date,shares,price);
}


QString investment::getSingleInflationProfit(std::string date, double investedMoney, double shares) {
    std::array inflation = {1.006, 0.936, 0.907, 0.897, 0.992, 1.008, 1.015, 1.03, 1.014, 1.029, 0.972, 1.000,1.007,1.099, 1.030, 1.023, 1.022, 1.181, 1.088, 1.03, 0.979, 1.059, 1.060, 1.008, 1.007, 0.993, 1.004, 1.03, 1.029, 1.018, 1.017, 1.014, 1.007, 1.013, 1.016, 1.010, 1.019, 1.035, 1.030, 1.047, 1.062, 1.056, 1.033, 1.034, 1.087, 1.123, 1.069, 1.049, 1.090, 1.133, 1.125, 1.089, 1.038, 1.038, 1.039, 1.038, 1.010, 1.044, 1.044, 1.046, 1.061, 1.031, 1.029, 1.027, 1.027, 1.025, 1.033, 1.017, 1.016, 1.027, 1.034, 1.016, 1.024, 1.019, 1.033, 1.034, 1.025, 1.041, 1.001, 1.027, 1.015, 1.030, 1.017, 1.015, 1.080, 1.070, 1.021, 1.021, 1.019, 1.023, 1.014, 1.07, 1.065, 1.034};
    std::vector<std::string> dates;
    std::string item;
    std::stringstream ss(date);
    std::string stockdata = getRealTimeQuote(name.toStdString());
    using value = std::variant<double,std::string>;
    double currentValue = shares * currentPrice;

    while (std::getline(ss,item,'-')){
        dates.push_back(item);
    }
    std::string year = dates[0];
    int index = -1 * (2023 - std::stoi(year));
    double inflatedMoney = investedMoney;
    for (int i = index; i < -1; i++) {
        investedMoney *= inflation[index];

    }
    double profit = (currentValue - investedMoney);

    return QString::number(std::round(profit * 100) / 100, 'f', 2);


}
QString investment::getTotalInflationProfit() {
    totalProfitInflation = 0;
    for (const auto& [key, array] : investmentMap) {
        double quantity = std::stod(array[1].toStdString());
            double value = std::stod(array[2].toStdString());
        QString profitString = (getSingleInflationProfit(array[0].toStdString(),value,quantity));
        totalProfitInflation += profitString.toDouble();

    }

    return QString::number(totalProfitInflation);

}

std::string investment::getRealTimeQuote(const std::string &stock){
    std::string apiKey = (qgetenv("API_KEY")).toStdString();
    cpr::Response stockData = cpr::Get(cpr::Url{"https://fmpcloud.io/api/v3/quote/" + stock  + "?apikey=" + apiKey});
    return stockData.text;

}

