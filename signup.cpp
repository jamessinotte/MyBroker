#include "signup.h"
#include "ui_signup.h"

#include <string>
#include <iostream>




Signup::Signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signup)


{

    std::cout <<"signup" << std::endl;
    ui->setupUi(this);
    std::cout << "setupUi completed" << std::endl;
    if (ui->SignupButton) {
        std::cout << "SignupButton exists" << std::endl;


    }
    connect(ui->SignupButton,&QPushButton::clicked,this, [=](){
        checkInfo();
    });





}

Signup::~Signup()
{
    delete ui;
}

std::string Signup::getText(const QString type) const {
    QLineEdit *lineEdit = findChild<QLineEdit*>(type);
    std::string text = lineEdit->text().toStdString();

    return text;


}
void Signup::checkInfo() {
    std::cout << "Signupbutton" << std::endl;

    std::string password = getText("signupPassword");
    std::string confirmPassword = getText("confirmPassword");
    std::string email_ = getText("signupEmail");
    std::string username_ = getText("signupUsername");
    std::string firstName = getText("firstName");
    std::string lastName = getText("lastName");


    std::cout << "data" <<  password <<  confirmPassword <<  email_ <<  username_ <<  firstName <<  lastName << std::endl;
    std::cout << "Retrieved UI text fields" << std::endl << std::flush;
    std::array<std::string,6> info = {password, confirmPassword, email_, username_, firstName, lastName};
    bool error = false;
    for (int i = 0; i < 6; ++i) {
        if (info[i] == "" and error==false) {
            std::cout << "notext" << std::endl;
            error = true;
            errorHandle(info[i]);
        }
    }


    if (password != confirmPassword && error==false) {
        errorHandle("mismatchPassword");
        error = true;
    }




    if (error == false) {

        std::cout << "doc inserted" << std::endl;
    }
    emit switchUI("Login");



}
void Signup::errorHandle(std::string error) {
    std::cout << "error" << std::endl;
    if (error == "signupPassword" or error == "signupUsername" or error == "confirmPassword" or error == "signupPassowrd" or error == "firstName" or error == "lastName") {
        std::cout << "blank" << std::endl;
        ui->errorText->setText("please fill in all of the texts");

    }
    else if (error == "usernameExists"){
         std::cout << "username exists" << std::endl;
        ui->errorText->setText("Username already exists");
    }
    else if (error == "emailExists"){
        std::cout << "email exists" << std::endl;
        ui->errorText->setText("Email is already used");
    }
    else if (error == "mismatchPassword") {
        std::cout << "password mismatch" << std::endl;
        ui->errorText->setText("Passwords do not match");
    }




}



