#include <QApplication>

#include "mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu* main_menu = new MainMenu();

    main_menu->show();

    return a.exec();
}
