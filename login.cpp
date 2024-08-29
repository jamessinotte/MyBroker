#include "login.h"
#include <iostream>
Login::Login(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *loginButton = new QPushButton("Login", this);
    loginButton->setObjectName("loginButton");
    QLineEdit *loginEmail = new QLineEdit(this);
    loginEmail->setPlaceholderText("Email");
    loginEmail->setObjectName("loginEmail");
    QLineEdit *loginPassword = new QLineEdit(this);
    loginPassword->setPlaceholderText("Password");
    loginPassword->setObjectName("loginPassword");
    QPushButton *SignupPageButton = new QPushButton("Sign Up", this);
    SignupPageButton->setObjectName("SignupPageButton");
    QLabel *errorText = new QLabel(this);
    errorText->setObjectName("errorText");

    this->setStyleSheet(
        "QWidget {"
        "    background-color: #f7f7f7;"
        "    font-family: 'Segoe UI', Tahoma, Geneva, sans-serif;"
        "    font-size: 16px;"
        "    color: #333333;"
        "}"
        "QLineEdit {"
        "    background-color: #FFFFFF;"
        "    border: 1px solid #CCCCCC;"
        "    border-radius: 10px;"
        "    padding: 10px;"
        "    color: #333333;"
        "    font-size: 16px;"
        "    margin-bottom: 20px;"
        "    width: 350px;"
        "}"
        "QPushButton {"
        "    background-color: #6a11cb;"
        "    color: #FFFFFF;"
        "    border: none;"
        "    border-radius: 20px;"
        "    padding: 10px 20px;"
        "    font-size: 16px;"
        "    width: 350px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #7f39fb;"
        "}"
        "QLabel {"
        "    color: #333333;"
        "    font-weight: bold;"
        "}"
        "#errorText {"
        "    color: #FF0000;"
        "    margin-top: 10px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        );

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QLabel *welcomeLabel = new QLabel("Welcome Back!", this);
    QLabel *loginPromptLabel = new QLabel("Log in to continue.", this);

    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->addStretch();
    textLayout->addWidget(welcomeLabel, 0, Qt::AlignCenter);
    textLayout->addWidget(loginPromptLabel, 0, Qt::AlignCenter);
    textLayout->addStretch();

    QWidget *leftContainer = new QWidget(this);
    leftContainer->setStyleSheet("background-color: #6a11cb;");
    leftContainer->setLayout(textLayout);

    welcomeLabel->setStyleSheet(
        "color: white;"
        "font-size: 36px;"
        "font-weight: bold;"
        "background: transparent;"
        );

    loginPromptLabel->setStyleSheet(
        "color: white;"
        "font-size: 24px;"
        "background: transparent;"
        );

    mainLayout->addWidget(leftContainer, 1);

    QWidget *formContainer = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    QLabel *formTitle = new QLabel("Log In", formContainer);
    formTitle->setStyleSheet("font-size: 24px; color: #6a11cb; margin-bottom: 20px;");
    formLayout->addWidget(formTitle, 0, Qt::AlignLeft);
    formLayout->addWidget(loginEmail);
    formLayout->addWidget(loginPassword);
    formLayout->addWidget(loginButton);
    formLayout->addWidget(SignupPageButton);
    formLayout->addWidget(errorText);
    formLayout->setAlignment(Qt::AlignCenter);
    formLayout->setSpacing(20);

    mainLayout->addWidget(formContainer, 0, Qt::AlignRight | Qt::AlignVCenter);

    auto applyShadow = [](QWidget* widget) {
        QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
        shadowEffect->setBlurRadius(15.0);
        shadowEffect->setOffset(2.0, 2.0);
        shadowEffect->setColor(QColor(0, 0, 0, 80));
        widget->setGraphicsEffect(shadowEffect);
    };

    applyShadow(loginEmail);
    applyShadow(loginPassword);
    applyShadow(loginButton);
    applyShadow(SignupPageButton);

    this->setLayout(mainLayout);

    connect(loginButton, &QPushButton::clicked, this, [=]() {
        if (signin()) {
            emit switchToHomepage();
        } else {
            errorText->setText("Login failed. Please check your email and password.");
        }
    });

    connect(SignupPageButton, &QPushButton::clicked, this, &Login::onSignupButtonClicked);
}

Login::~Login()
{
    delete ui;
}

bool Login::signin() {
    database& db = database::getInstance();
    QString email = getText(this, "loginEmail");
    QString password = getText(this, "loginPassword");
    bool login = db.checkLogin(email, password);
    return login;
}

void Login::onSignupButtonClicked() {
    emit switchToSignup();
}

void Login::error() {
}
