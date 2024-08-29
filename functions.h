#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QEvent>
#include <QObject>




class functions
{
public:
    functions();
    QString getText(QObject *parent, std::string type);
    bool eventFilter(QObject *obj, QEvent *event);
private:
    QWidget *currentWidget;
    QMainWindow *window;
};

#endif // FUNCTIONS_H
