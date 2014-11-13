#include <QApplication>

#include "mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu* main_menu = new MainMenu();

    main_menu->move(QApplication::desktop()->screen()->rect().center() - main_menu->rect().center());

    main_menu->show();

    return a.exec();
}
