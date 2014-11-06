#include <QApplication>

#include "mainmenu.h"
#include "options.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainMenu* main_menu = new MainMenu();

//    main_menu->move(QApplication::desktop()->screen()->rect().center() - main_menu->rect().center());

//    main_menu->show();

    Options* options = new Options();

    options->show();

    return a.exec();
}
