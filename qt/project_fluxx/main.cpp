#include <QApplication>

#include "mywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWidget* mainMenu = new MyWidget();

    mainMenu->show();

    return a.exec();
}
