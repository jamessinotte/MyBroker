#include "uimanager.h"
#include <iostream>

UiManager::UiManager(QWidget *parent) :
    QWidget(parent),
    stackedWidget(new QStackedWidget(this)),

    loginUi(new Login(this)),
    signupUi(new Signup(this)),
    homepageUi(new Homepage(this))

{




    stackedWidget->addWidget(loginUi);
    stackedWidget->addWidget(signupUi);
    stackedWidget->addWidget(homepageUi);



    stackedWidget->setCurrentWidget(loginUi);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);







    connect(signupUi, &Signup::switchToLogin, this, &UiManager::switchToLogin);
    connect(loginUi, &Login::switchToSignup, this, &UiManager::switchToSignup);
    connect(loginUi, &Login::switchToHomepage, this, &UiManager::switchToHomepage);

}

UiManager::~UiManager()
{
    delete stackedWidget;
}

void UiManager::switchToSignup()
{
    stackedWidget->setCurrentWidget(signupUi);
}

void UiManager::switchToLogin()
{
    stackedWidget->setCurrentWidget(loginUi);
}
void UiManager::switchToHomepage() {

    stackedWidget->setCurrentWidget(homepageUi);
    homepageUi->displayStocks();


}
