#include "mainmenu.h"
#include "newgame.h"
#include "start.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent)
{
   main_layout = new QVBoxLayout();
   start_widget = new Start(this);
   //options_widget = new options();
   //newgame_widget = new NewGame(this);

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

    delete start_widget;
}

void MainMenu::newGameBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(newgame_widget);

   delete newgame_widget;
}

//void MainMenu::options()
//{
//    options_widget = new Options(this);
//    main_layout->addWidget(options_widget);
//    main_layout->removeWidget(start_widget);

//    delete start_widget;
//}

//void MainMenu::optionsBack()
//{
//    start_widget = new Start(this);
//    main_layout->addWidget(start_widget);
//    main_layout->removeWidget(options_widget);

//   delete options_widget;
//}
