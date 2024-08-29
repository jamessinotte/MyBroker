#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QSqlQuery>

#include <QDebug>
#include <iostream>
#include <cpr/cpr.h>


class database {
public:
    static database& getInstance();
    bool connect();
    bool checkSignup(const QString &username, const QString &email);
    void insertSignup(const QString &firstName, const QString &lastName, const QString &email, const QString &password, const QString &username);
    bool checkLogin (const QString &email, const QString &password);
    QString error;
    QSqlDatabase getDatabase();
    int userid;
    void addInvestment(QString &stock, QString date, QString quanity, QString value);
    void deleteInvestment(std::string id, QString stockname);
    std::vector<std::string> stockList();
    std::map<int, std::array<QString,3>> searchInvestments(QString &stock);
    bool signedin = false;

private:
    database();
    QSqlDatabase db;
    bool connected = false;
    ~database();
    database(const database&) = delete;
    database& operator=(const database&) = delete;
};

#endif // DATABASE_H
