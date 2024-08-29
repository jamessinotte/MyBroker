#include "homepage.h"
#include "ui_homepage.h"
#include <iostream>

Homepage::Homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Homepage)
{
    ui->setupUi(this);
}

Homepage::~Homepage()
{
    delete ui;
}

QString Homepage::generateRandomKey(int length) {
    QString key;
    for (int i = 0; i < length; ++i) {
        key.append(QString::number(QRandomGenerator::global()->bounded(10)));
    }
    return key;
}

void Homepage::addStock() {
    QString date = findChild<QLineEdit*>("dateEdit")->text();
    QString stock = findChild<QLineEdit*>("stockNameEdit")->text();
    double shares = findChild<QLineEdit*>("sharesEdit")->text().toDouble();
    double price = findChild<QLineEdit*>("priceEdit")->text().toDouble();
    QString qKey = generateRandomKey(8);

    bool isNewStock = (stocks.find(stock) == stocks.end());
    investment* Investment = nullptr;
    QVBoxLayout* stockSectionLayout = nullptr;
    QGridLayout* stockGridLayout = nullptr;
    QWidget* stockSectionWidget = nullptr;

    if (isNewStock) {
        db.addInvestment(stock, date, QString::number(shares), QString::number(price));
        stocks[stock] = std::make_unique<investment>(stock);
        Investment = stocks[stock].get();

        stockSectionWidget = new QWidget(containerWidget);
        stockSectionLayout = new QVBoxLayout(stockSectionWidget);
        stockSectionLayout->setAlignment(Qt::AlignTop);
        stockSectionWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        stockSectionWidget->setObjectName("stockSectionWidget" + stock);

        QLabel* stockHeaderLabel = new QLabel(stock + "  $" + QString::number(Investment->currentPrice, 'f', 2));
        stockHeaderLabel->setStyleSheet("font-weight: bold; font-size: 24px; color: #6a11cb; margin-bottom: 20px;");
        stockSectionLayout->addWidget(stockHeaderLabel);

        stockGridLayout = new QGridLayout();
        stockGridLayout->setObjectName("stockGridLayout" + stock);
        stockSectionLayout->addLayout(stockGridLayout);

        QLabel* totalProfitLabel = new QLabel("Total Profit: $0");
        QLabel* totalInflationProfitLabel = new QLabel("Total Inflation Profit: $0");
        totalProfitLabel->setObjectName("totalProfitLabel" + stock);
        totalInflationProfitLabel->setObjectName("totalInflationProfitLabel" + stock);

        totalProfitLabel->setStyleSheet("font-weight: bold; color: #6a11cb; margin-top: 10px;");
        totalInflationProfitLabel->setStyleSheet("font-weight: bold; color: #6a11cb; margin-top: 10px;");

        stockSectionLayout->addWidget(totalProfitLabel);
        stockSectionLayout->addWidget(totalInflationProfitLabel);

        stocksLayout->addWidget(stockSectionWidget);
    } else {
        Investment = stocks[stock].get();
        Investment->addInvestment(qKey.toInt(), date, QString::number(shares), QString::number(price));
        stockSectionWidget = findChild<QWidget*>("stockSectionWidget" + stock);
        stockSectionLayout = qobject_cast<QVBoxLayout*>(stockSectionWidget->layout());
        stockGridLayout = findChild<QGridLayout*>("stockGridLayout" + stock);
    }

    QWidget* rowWidget = new QWidget(containerWidget);
    QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
    rowWidget->setObjectName(qKey);
    rowWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel* dateLabel = new QLabel(date);
    QLabel* sharesLabel = new QLabel(QString::number(shares, 'f', 2));
    QLabel* costLabel = new QLabel("$" + QString::number(price, 'f', 2));
    QLabel* valueLabel = new QLabel("$" + QString::number(Investment->currentPrice * shares, 'f', 2));
    QLabel* profitLabel = new QLabel("$" + Investment->getSingleProfit(shares, price, stock.toStdString()));

    dateLabel->setAlignment(Qt::AlignCenter);
    sharesLabel->setAlignment(Qt::AlignCenter);
    costLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setAlignment(Qt::AlignCenter);
    profitLabel->setAlignment(Qt::AlignCenter);

    dateLabel->setStyleSheet("color: #333333; font-size: 16px;");
    sharesLabel->setStyleSheet("color: #333333; font-size: 16px;");
    costLabel->setStyleSheet("color: #333333; font-size: 16px;");
    valueLabel->setStyleSheet("color: #333333; font-size: 16px;");
    profitLabel->setStyleSheet("color: #333333; font-size: 16px;");

    rowLayout->addWidget(dateLabel);
    rowLayout->addWidget(sharesLabel);
    rowLayout->addWidget(costLabel);
    rowLayout->addWidget(valueLabel);
    rowLayout->addWidget(profitLabel);

    QPushButton* deleteButton = new QPushButton("Delete");
    deleteButton->setMaximumWidth(100);
    deleteButton->setStyleSheet(
        "QPushButton { background-color: #6a11cb; color: #ffffff; border-radius: 20px; padding: 10px 20px; font-size: 16px; }"
        "QPushButton:hover { background-color: #7f39fb; }"
        );
    connect(deleteButton, &QPushButton::clicked, this, [this, qKey, stock]() {
        handleDeleteButton(qKey, stock);
    });
    rowLayout->addWidget(deleteButton);

    int newRow = stockGridLayout->rowCount();
    stockGridLayout->addWidget(rowWidget, newRow, 0, 1, 6);

    if (newRow > 1) {
        rowWidget->setVisible(false);
    }

    rowWidget->setStyleSheet(
        "QWidget { border-bottom: 1px solid #7f39fb; margin-bottom: 1px; }"
        );

    QPushButton* showMoreButton = findChild<QPushButton*>("showMoreButton" + stock);
    if (!showMoreButton) {
        showMoreButton = new QPushButton("Show More");
        showMoreButton->setObjectName("showMoreButton" + stock);
        showMoreButton->setStyleSheet(
            "QPushButton { background-color: #6a11cb; color: #ffffff; border-radius: 20px; padding: 10px 20px; font-size: 16px; margin-top: 10px; }"
            "QPushButton:hover { background-color: #7f39fb; }"
            );
        stockSectionLayout->addWidget(showMoreButton);

        connect(showMoreButton, &QPushButton::clicked, this, [stockGridLayout, showMoreButton, stockSectionWidget]() {
            bool anyHidden = false;
            for (int i = 1; i < stockGridLayout->rowCount(); ++i) {
                QWidget* row = stockGridLayout->itemAtPosition(i, 0)->widget();
                if (row && !row->isVisible()) {
                    row->setVisible(true);
                    anyHidden = true;
                }
            }
            if (anyHidden) {
                showMoreButton->setText("Show Less");
                stockSectionWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            } else {
                for (int i = 1; i < stockGridLayout->rowCount(); ++i) {
                    QWidget* row = stockGridLayout->itemAtPosition(i, 0)->widget();
                    if (row && row->isVisible()) {
                        row->setVisible(false);
                    }
                }
                showMoreButton->setText("Show More");
                stockSectionWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            }
            stockSectionWidget->adjustSize();
        });
    }

    updateProfitLabels(stock);
}

void Homepage::updateProfitLabels(const QString& stockName) {
    auto stockIt = stocks.find(stockName);
    if (stockIt != stocks.end()) {
        QString totalProfitText = "Total Profit: $" + stockIt->second->getTotalProfit();
        QString totalInflationProfitText = "Total Inflation Profit: $" + stockIt->second->getTotalInflationProfit();

        QLabel* totalProfitLabel = findChild<QLabel*>("totalProfitLabel" + stockName);
        QLabel* totalInflationProfitLabel = findChild<QLabel*>("totalInflationProfitLabel" + stockName);

        if (totalProfitLabel) {
            totalProfitLabel->setText(totalProfitText);
            totalProfitLabel->setStyleSheet("font-weight: bold; color: #6a11cb; margin-top: 10px;");
        }
        if (totalInflationProfitLabel) {
            totalInflationProfitLabel->setText(totalInflationProfitText);
            totalInflationProfitLabel->setStyleSheet("font-weight: bold; color: #6a11cb; margin-top: 10px;");
        }
    }
}

void Homepage::displayStocks() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);

    QWidget* formWidget = new QWidget(this);
    QFormLayout* formLayout = new QFormLayout(formWidget);

    QLineEdit* dateEdit = new QLineEdit("YYYY-MM-DD", formWidget);
    dateEdit->setObjectName("dateEdit");
    QLineEdit* stockNameEdit = new QLineEdit("AAPL", formWidget);
    stockNameEdit->setObjectName("stockNameEdit");
    QLineEdit* sharesEdit = new QLineEdit("", formWidget);
    sharesEdit->setObjectName("sharesEdit");
    QLineEdit* priceEdit = new QLineEdit("", formWidget);
    priceEdit->setObjectName("priceEdit");

    dateEdit->setMaximumWidth(350);
    stockNameEdit->setMaximumWidth(350);
    sharesEdit->setMaximumWidth(350);
    priceEdit->setMaximumWidth(350);

    dateEdit->setStyleSheet(
        "QLineEdit { background-color: #FFFFFF; border: 1px solid #CCCCCC; border-radius: 10px; padding: 10px; font-size: 16px; color: #333333; }"
        );
    stockNameEdit->setStyleSheet(
        "QLineEdit { background-color: #FFFFFF; border: 1px solid #CCCCCC; border-radius: 10px; padding: 10px; font-size: 16px; color: #333333; }"
        );
    sharesEdit->setStyleSheet(
        "QLineEdit { background-color: #FFFFFF; border: 1px solid #CCCCCC; border-radius: 10px; padding: 10px; font-size: 16px; color: #333333; }"
        );
    priceEdit->setStyleSheet(
        "QLineEdit { background-color: #FFFFFF; border: 1px solid #CCCCCC; border-radius: 10px; padding: 10px; font-size: 16px; color: #333333; }"
        );

    formLayout->addRow("Date", dateEdit);
    formLayout->addRow("Stock Name", stockNameEdit);
    formLayout->addRow("Shares", sharesEdit);
    formLayout->addRow("Price", priceEdit);

    QPushButton* addStockButton = new QPushButton("Add Stock", formWidget);
    addStockButton->setMaximumWidth(350);
    addStockButton->setStyleSheet(
        "QPushButton { background-color: #6a11cb; color: #ffffff; border-radius: 20px; padding: 10px 20px; font-size: 16px; }"
        "QPushButton:hover { background-color: #7f39fb; }"
        );

    formLayout->addWidget(addStockButton);
    connect(addStockButton, &QPushButton::clicked, this, &Homepage::addStock);
    QLabel *Welcome = new QLabel(this);
    Welcome->setText("MyPortforlio");
    Welcome->setStyleSheet(
        "QLabel { "
        "color: #6a11cb; "
        "font-size: 150px; "
        "font-weight: bold; "
        "padding: 10px 20px; "
        "margin-bottom: 20px; "
        "}"
        );
    QHBoxLayout* formLayoutWrapper = new QHBoxLayout();
    formLayoutWrapper->setContentsMargins(5, 5, 5, 5);
    formLayoutWrapper->addWidget(Welcome,0,Qt::AlignTop | Qt::AlignLeft);
    formLayoutWrapper->addStretch();
    formLayoutWrapper->addWidget(formWidget, 0, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addLayout(formLayoutWrapper);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    containerWidget = new QWidget();
    QGridLayout* stocksGridLayout = new QGridLayout(containerWidget);
    containerWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    stocksGridLayout->setObjectName("stocksGridLayout");
    stocksGridLayout->setContentsMargins(5, 5, 5, 5);
    stocksGridLayout->setSpacing(20);

    scrollArea->setStyleSheet(
        "QScrollArea { border: none; background-color: #f7f7f7; }"
        );
    containerWidget->setStyleSheet(
        "QWidget { background-color: #f7f7f7; }"
        );

    stockList = db.stockList();
    int column = 0;
    int row = 0;
    for (const auto& stock : stockList) {
        QString stockname = QString::fromStdString(stock);
        stocks[stockname] = std::make_unique<investment>(stockname);

        QWidget* stockSectionWidget = new QWidget(containerWidget);
        QVBoxLayout* stockSectionLayout = new QVBoxLayout(stockSectionWidget);
        stockSectionLayout->setAlignment(Qt::AlignTop);
        stockSectionWidget->setObjectName("stockSectionWidget" + stockname);
        stockSectionWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        stockSectionWidget->setStyleSheet(
            "QWidget { background-color: #ffffff; border-radius: 20px; padding: 10px; }"
            );

        QLabel* stockHeaderLabel = new QLabel(stockname + "  $" + QString::number(stocks[stockname]->currentPrice, 'f', 2));
        stockHeaderLabel->setStyleSheet("font-weight: bold; font-size: 24px; color: #6a11cb; margin-bottom: 20px;");
        stockSectionLayout->addWidget(stockHeaderLabel);

        QGridLayout* stockGridLayout = new QGridLayout();
        stockGridLayout->setObjectName("stockGridLayout" + stockname);

        stockGridLayout->addWidget(new QLabel("Date"), 0, 0, Qt::AlignCenter);
        stockGridLayout->addWidget(new QLabel("Shares"), 0, 1, Qt::AlignCenter);
        stockGridLayout->addWidget(new QLabel("Cost"), 0, 2, Qt::AlignCenter);
        stockGridLayout->addWidget(new QLabel("Value"), 0, 3, Qt::AlignCenter);
        stockGridLayout->addWidget(new QLabel("Profit"), 0, 4, Qt::AlignCenter);

        for (int i = 0; i < 5; ++i) {
            QLabel* headerLabel = qobject_cast<QLabel*>(stockGridLayout->itemAtPosition(0, i)->widget());
            if (headerLabel) {
                headerLabel->setStyleSheet("font-weight: bold; color: #6a11cb; font-size: 16px;");
            }
        }

        int currentRow = 1;
        for (const auto& [key, value] : stocks[stockname]->investmentMap) {
            QWidget* rowWidget = new QWidget();
            QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
            rowLayout->setAlignment(Qt::AlignTop);
            QString qKey = QString::number(key);
            rowWidget->setObjectName(qKey);
            rowWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

            rowWidget->setStyleSheet(
                "QWidget { border: none; border-bottom: 1px solid #7f39fb; margin-bottom: 2px; }"
                );

            QLabel* dateLabel = new QLabel(value[0]);
            QLabel* sharesLabel = new QLabel(QString::number(value[1].toDouble(), 'f', 2));
            QLabel* costLabel = new QLabel("$" + QString::number(value[2].toDouble(), 'f', 2));
            QLabel* valueLabel = new QLabel("$" + QString::number(stocks[stockname]->currentPrice * value[2].toDouble(), 'f', 2));
            QLabel* profitLabel = new QLabel("$" + stocks[stockname]->getSingleProfit(value[2].toDouble(), value[1].toDouble(), stockname.toStdString()));

            dateLabel->setAlignment(Qt::AlignCenter);
            sharesLabel->setAlignment(Qt::AlignCenter);
            costLabel->setAlignment(Qt::AlignCenter);
            valueLabel->setAlignment(Qt::AlignCenter);
            profitLabel->setAlignment(Qt::AlignCenter);

            dateLabel->setStyleSheet("color: #333333; font-size: 16px;");
            sharesLabel->setStyleSheet("color: #333333; font-size: 16px;");
            costLabel->setStyleSheet("color: #333333; font-size: 16px;");
            valueLabel->setStyleSheet("color: #333333; font-size: 16px;");
            profitLabel->setStyleSheet("color: #333333; font-size: 16px;");

            rowLayout->addWidget(dateLabel);
            rowLayout->addWidget(sharesLabel);
            rowLayout->addWidget(costLabel);
            rowLayout->addWidget(valueLabel);
            rowLayout->addWidget(profitLabel);

            QPushButton* deleteButton = new QPushButton("Delete");
            deleteButton->setMaximumWidth(100);
            deleteButton->setStyleSheet(
                "QPushButton { background-color: #6a11cb; color: #ffffff; border-radius: 20px; padding: 10px 20px; font-size: 16px; }"
                "QPushButton:hover { background-color: #7f39fb; }"
                );
            connect(deleteButton, &QPushButton::clicked, this, [this, qKey = QString::number(key), stockname]() {
                handleDeleteButton(qKey, stockname);
            });
            rowLayout->addWidget(deleteButton);

            if (currentRow > 1) {
                rowWidget->setVisible(false);
            }

            stockGridLayout->addWidget(rowWidget, currentRow++, 0, 1, 6);
        }
        stockGridLayout->setAlignment(Qt::AlignTop);

        QLabel* totalProfit = new QLabel("Total Profit: $" + stocks[stockname]->getTotalProfit());
        QLabel* totalInflationProfit = new QLabel("Total Inflation Profit: $" + stocks[stockname]->getTotalInflationProfit());

        totalProfit->setObjectName("totalProfitLabel" + stockname);
        totalInflationProfit->setObjectName("totalInflationProfitLabel" + stockname);

        totalProfit->setStyleSheet("font-weight: bold; color: #6a11cb; margin-top: 10px;");
        totalInflationProfit->setStyleSheet("font-weight: bold; color: #6a11cb; margin-top: 10px;");

        stockSectionLayout->addLayout(stockGridLayout);
        stockSectionLayout->addWidget(totalProfit);
        stockSectionLayout->addWidget(totalInflationProfit);

        QPushButton* showMoreButton = new QPushButton("Show More");
        showMoreButton->setObjectName("showMoreButton" + stockname);
        showMoreButton->setStyleSheet(
            "QPushButton { background-color: #6a11cb; color: #ffffff; border-radius: 20px; padding: 10px 20px; font-size: 16px; margin-top: 10px; }"
            "QPushButton:hover { background-color: #7f39fb; }"
            );
        stockSectionLayout->addWidget(showMoreButton);

        connect(showMoreButton, &QPushButton::clicked, this, [stockGridLayout, showMoreButton, stockSectionWidget]() {
            bool anyHidden = false;
            int visibleRows = 0;
            for (int i = 1; i < stockGridLayout->rowCount(); ++i) {
                QWidget* row = stockGridLayout->itemAtPosition(i, 0)->widget();
                if (row && !row->isVisible()) {
                    row->setVisible(true);
                    anyHidden = true;
                }
                visibleRows++;
            }
            if (anyHidden) {
                showMoreButton->setText("Show Less");
                stockSectionWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            } else {
                for (int i = 1; i < stockGridLayout->rowCount(); ++i) {
                    QWidget* row = stockGridLayout->itemAtPosition(i, 0)->widget();
                    if (row && row->isVisible()) {
                        row->setVisible(false);
                    }
                }
                visibleRows = 1;
                showMoreButton->setText("Show More");
                stockSectionWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            }
            int rowHeight = stockGridLayout->itemAtPosition(1, 0)->widget()->sizeHint().height();
            int totalHeight = rowHeight * visibleRows + showMoreButton->sizeHint().height();
            stockSectionWidget->setMinimumHeight(totalHeight);

            stockSectionWidget->adjustSize();
            stockSectionWidget->updateGeometry();
            stockSectionWidget->adjustSize();
            stockSectionWidget->parentWidget()->adjustSize();
            stockSectionWidget->parentWidget()->updateGeometry();
        });

        stocksGridLayout->addWidget(stockSectionWidget, row, column);

        column++;
        if (column == 2) {
            column = 0;
            row++;
        }
    }

    scrollArea->setWidget(containerWidget);
    mainLayout->addWidget(scrollArea);

    this->setLayout(mainLayout);
    this->show();
}

void Homepage::handleDeleteButton(QString qKey, QString stockName) {
    auto stockIt = stocks.find(stockName);
    if (stockIt == stocks.end()) {
        return;
    }

    auto& investmentMap = stockIt->second->investmentMap;
    auto investmentIt = investmentMap.find(qKey.toInt());
    db.deleteInvestment(qKey.toStdString(), stockName);

    if (investmentIt != investmentMap.end()) {
        investmentMap.erase(investmentIt);
    }

    QWidget* rowWidget = findChild<QWidget*>(qKey);
    if (rowWidget) {
        QVBoxLayout* stockSectionLayout = dynamic_cast<QVBoxLayout*>(rowWidget->parentWidget()->layout());
        if (stockSectionLayout) {
            stockSectionLayout->removeWidget(rowWidget);
            rowWidget->deleteLater();
        }
    }

    if (investmentMap.empty()) {
        QWidget* stockSectionWidget = findChild<QWidget*>("stockSectionWidget" + stockName);
        if (stockSectionWidget) {
            stocksLayout->removeWidget(stockSectionWidget);
            stockSectionWidget->deleteLater();
        }
    } else {
        updateProfitLabels(stockName);
    }
}

