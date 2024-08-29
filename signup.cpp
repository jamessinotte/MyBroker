#include "signup.h"
#include <iostream>

Signup::Signup(QWidget *parent)
    : QWidget(parent)
{
    QWidget::showFullScreen();

    QPushButton *signupButton = new QPushButton("Sign Up", this);
    signupButton->setObjectName("signupButton");
    QLineEdit *confirmPassword = new QLineEdit(this);
    confirmPassword->setPlaceholderText("Confirm Password");
    QLineEdit *firstName = new QLineEdit(this);
    firstName->setPlaceholderText("First Name");
    firstName->setObjectName("firstName");
    QLineEdit *lastName = new QLineEdit(this);
    lastName->setPlaceholderText("Last Name");
    lastName->setObjectName("lastName");
    QLineEdit *signupEmail = new QLineEdit(this);
    signupEmail->setPlaceholderText("Email");
    signupEmail->setObjectName("signupEmail");
    QLineEdit *signupPassword = new QLineEdit(this);
    signupPassword->setPlaceholderText("Password");
    signupPassword->setObjectName("signupPassword");
    QLineEdit *signupUsername = new QLineEdit(this);
    signupUsername->setPlaceholderText("Username");
    signupUsername->setObjectName("signupUsername");
    QLabel *errorText = new QLabel(this);
    QPushButton *loginPageButton = new QPushButton("Login", this);

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

    QWidget *leftContainer = new QWidget(this);
    leftContainer->setStyleSheet("background-color: #6a11cb;");
    QVBoxLayout *leftLayout = new QVBoxLayout(leftContainer);

    QLabel *welcomeLabel = new QLabel("Welcome To MyBroker", leftContainer);
    welcomeLabel->setStyleSheet(
        "font-size: 36px;"
        "font-weight: bold;"
        "color: #FFFFFF;"
        );
    welcomeLabel->setAlignment(Qt::AlignCenter);

    QLabel *profitsLabel = new QLabel("See Your Profits Today!", leftContainer);
    profitsLabel->setStyleSheet(
        "font-size: 24px;"
        "color: #FFFFFF;"
        "background: transparent;"
        );
    profitsLabel->setAlignment(Qt::AlignCenter);

    leftLayout->addStretch();
    leftLayout->addWidget(welcomeLabel);
    leftLayout->addWidget(profitsLabel);
    leftLayout->addStretch();
    leftLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(leftContainer, 1);

    QGraphicsDropShadowEffect *welcomeShadow = new QGraphicsDropShadowEffect();
    welcomeShadow->setBlurRadius(15.0);
    welcomeShadow->setOffset(2.0, 2.0);
    welcomeShadow->setColor(QColor(0, 0, 0, 80));
    welcomeLabel->setGraphicsEffect(welcomeShadow);
    profitsLabel->setGraphicsEffect(welcomeShadow);

    QWidget *formContainer = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    QLabel *formTitle = new QLabel("Sign Up Now", formContainer);
    formTitle->setStyleSheet("font-size: 24px; color: #6a11cb; margin-bottom: 20px;");
    formLayout->addWidget(formTitle, 0, Qt::AlignLeft);
    formLayout->addWidget(signupEmail);
    formLayout->addWidget(signupUsername);
    formLayout->addWidget(signupPassword);
    formLayout->addWidget(confirmPassword);
    formLayout->addWidget(firstName);
    formLayout->addWidget(lastName);
    formLayout->addWidget(signupButton);
    formLayout->addWidget(loginPageButton);
    formLayout->setAlignment(Qt::AlignCenter);
    formLayout->setSpacing(20);

    mainLayout->addWidget(formContainer, 0, Qt::AlignRight | Qt::AlignVCenter);

    this->setLayout(mainLayout);

    connect(signupButton, &QPushButton::clicked, this, [=]() {
        checkInfo(signupUsername, signupEmail, signupPassword, confirmPassword, firstName, lastName, errorText);
        emit switchToLogin();
    });

    connect(loginPageButton, &QPushButton::clicked, this, &Signup::switchToLogin);
}

Signup::~Signup()
{
}

void Signup::checkInfo(QLineEdit* signupUsername, QLineEdit* signupEmail, QLineEdit* signupPassword, QLineEdit* confirmPassword, QLineEdit* firstName, QLineEdit* lastName, QLabel* errorText) {
    database& db = database::getInstance();

    QString username = signupUsername->text();
    QString email = signupEmail->text();
    QString password = signupPassword->text();
    QString confirmPass = confirmPassword->text();
    QString fname = firstName->text();
    QString lname = lastName->text();

    if (username.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPass.isEmpty() || fname.isEmpty() || lname.isEmpty()) {
        errorText->setText("Please fill in all of the fields.");
        return;
    }

    if (password != confirmPass) {
        errorText->setText("Passwords do not match.");
        return;
    }

    if (!db.checkSignup(username, email)) {
        errorText->setText(db.error);
        return;
    }

    db.insertSignup(fname, lname, email, password, username);
    emit switchToLogin();
}





