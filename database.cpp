#include "database.h"
#include <iostream>

database::database() {

}
database::~database() {
    // Destructor definition
    if (db.isOpen()) {
        db.close();
    }
}

database& database::getInstance()

{

    static database instance;
    return instance;

}

bool database::connect() {
    if (database::connected) {
        return true;
    }

    try {
        db = QSqlDatabase::addDatabase("QODBC");
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown exception caught." << std::endl;
        return false;
    }


    db.setDatabaseName("MySQLServerDataSource");
    db.setUserName(qgetenv("DB_USERNAME"));
    db.setPassword(qgetenv("DB_PASSWORD"));


    if (!db.open()) {
        QSqlError error = db.lastError();
        qDebug() << "Database error: " << error.text();
        return false;
    }


    database::connected = true;
    return true;
}

void database::insertSignup(const QString &firstName, const QString &lastName, const QString &email, const QString &password, const QString &username) {
    if (!db.open()) {
        QSqlError error = db.lastError();
        qDebug() << "Database error: " << error.text();
        return;
    }

    QSqlQuery query;

    QString insertQuery = "INSERT INTO dbo.users (firstName, lastName, email, password, username) VALUES (?, ?, ?, ?, ?)";
    query.prepare(insertQuery);
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(email);
    query.addBindValue(password);
    query.addBindValue(username);

    if (!query.exec()) {
        qDebug() << "Error inserting data:" << query.lastError();
    } else {
        qDebug() << "Record inserted successfully.";
    }
    db.close();
}

bool database::checkSignup(const QString &username, const QString &email) {
    QSqlQuery query;

    QString selectQueryEmail = "SELECT COUNT(*) FROM dbo.users WHERE email = ?";
    query.prepare(selectQueryEmail);
    query.addBindValue(email);
    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        error = "Email already exists";
        return false;
    }

    QString selectQueryUsername = "SELECT COUNT(*) FROM dbo.users WHERE username = ?";
    query.prepare(selectQueryUsername);
    query.addBindValue(username);
    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        error = "Username already exists";
        return false;
    }

    return true;
}
bool database::checkLogin(const QString &email, const QString &password) {

    QSqlQuery query;
    QString queryStatement = "SELECT COUNT(*) FROM users WHERE email = :email AND password = :password;";
    query.prepare(queryStatement);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        return false;
    }
    else {
        queryStatement = "SELECT id FROM users WHERE email = :email;";
        query.prepare(queryStatement);
        query.bindValue(":email",email);
        if (query.exec()) {
            if (query.next()) {
                userid = query.value(0).toInt();

            } else {

                qDebug() << "No user found with the provided email.";
            }

        return true;
    }
    }
    signedin = true;
    return true;

}
QSqlDatabase database::getDatabase() {
    return db;

}
void database::addInvestment(QString &stock, QString date, QString quantity, QString value) {
    QSqlQuery query;
    QString queryStatement = "INSERT INTO Investments (stock, date, shares, value, userid) "
                             "VALUES (:stock, :date, :shares, :value, :userid)";

    query.prepare(queryStatement);
    query.bindValue(":stock", stock);
    query.bindValue(":date", date);
    query.bindValue(":shares", quantity);
    query.bindValue(":value", value);
    query.bindValue(":userid", userid);
    if (!query.exec()) {

        QSqlError error = db.lastError();

    }
    QString queryString = "SELECT 1 FROM Stocks WHERE stock_name = :stock_name AND userid = :userid";

    query.prepare(queryString);
    query.bindValue(":stock_name",stock);
    query.bindValue(":userid", userid);
    if (!query.exec() || !query.next()) {


        QString insertQuery = "INSERT INTO Stocks (stock_name, userid) "
                                "VALUES(:stock_name, :userid)";
        query.prepare(insertQuery);
        query.bindValue(":stock_name", stock);
        query.bindValue(":userid",userid);
        if (!query.exec()) {
            QSqlError error = db.lastError();

            };


    }


}
std::map<int, std::array<QString,3>> database::searchInvestments(QString &stock) {
    std::map<int, std::array<QString,3>> investmentMap;
    QString queryStatement = "SELECT id, stock, date, shares, value FROM Investments "
                             "WHERE stock = :stock AND userid = :userid";
    QSqlQuery query;
    query.prepare(queryStatement);
    query.bindValue(":stock", stock);
    query.bindValue(":userid", userid);
    if (query.exec()) {
        while (query.next()) {
            int id = query.value("id").toInt();
            QString date = query.value("date").toString();
            QString shares = query.value("shares").toString();
            QString value = query.value("value").toString();


            investmentMap[id] = {date,shares,value};


        }
    }
    return investmentMap;

}


std::vector<std::string> database::stockList() {
    std::vector<std::string> stockList;
    QSqlQuery query;
        QString queryStatement = "SELECT stock_name FROM Stocks "
                                 "WHERE userid = :userid";
    query.prepare(queryStatement);
    query.bindValue(":userid" ,userid);
    if (query.exec()) {
        while (query.next()){
            std::string stock = query.value("stock_name").toString().toStdString();
            stockList.push_back(stock);

        }
    }
    std::sort(stockList.begin(), stockList.end());
    return stockList;

}

void database::deleteInvestment(std::string stockid, QString stockname) {
    QSqlQuery query;
    QString queryStatement = "DELETE FROM Investments "
                             "WHERE userid = :userid AND id = :id";
    query.prepare(queryStatement);
    query.bindValue(":userid", userid);
    query.bindValue(":id", QString::fromStdString(stockid));
    query.exec();

    QString queryStatement2 = "SELECT FROM Investments "
                             "WHERE userid = :userid and stock = :stock";
    query.prepare(queryStatement2);
    query.bindValue(":userid",userid);
    query.bindValue(":stock",stockname);





}
