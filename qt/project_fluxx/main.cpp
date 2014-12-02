#include <QApplication>

#include "mainmenu.h"
#include "DeckParser.h"
#include "Deck.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DeckParser deck_parser;
    Deck* deck = deck_parser.deck_to_game("../../docs/Default.fluxx");

    MainMenu* main_menu = new MainMenu(deck);

    main_menu->move(QApplication::desktop()->screen()->rect().center() - main_menu->rect().center());

    main_menu->show();

    return a.exec();
}
