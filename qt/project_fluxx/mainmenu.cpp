#include "mainmenu.h"
#include "newgame.h"
#include "start.h"
#include "options.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent)
{
   main_layout = new QVBoxLayout();
   start_widget = new Start(this);

   this->setWindowTitle(QString("Main Menu"));
   this->setMinimumWidth(640);
   this->setMinimumHeight(480);

   main_layout->addWidget(start_widget);
   this->setLayout(main_layout);
}

MainMenu::~MainMenu()
{
}

void MainMenu::newGame()
{
    newgame_widget = new NewGame(this);
    main_layout->addWidget(newgame_widget);
    main_layout->removeWidget(start_widget);
    this->setWindowTitle(QString("New Game"));

    delete start_widget;
}

void MainMenu::newGameBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(newgame_widget);
    this->setWindowTitle(QString("Main Menu"));

   delete newgame_widget;
}

void MainMenu::options()
{
    options_widget = new Options(this);
    main_layout->addWidget(options_widget);
    main_layout->removeWidget(start_widget);
    this->setWindowTitle(QString("Options"));

    delete start_widget;
}

void MainMenu::optionsBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(options_widget);
    this->setWindowTitle(QString("Main Menu"));

   delete options_widget;
}
