#include "mainmenu.h"
#include "newgame.h"
#include "start.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent)
{
   main_layout = new QVBoxLayout();
   layouts = new QStackedWidget();
   start_widget = new Start(this);
   //options_widget = new options();
   newgame_widget = new NewGame();
   newgame_widget->setParent(this);

   this->setWindowTitle(QString("Main Menu"));
   this->setMinimumWidth(640);
   this->setMinimumHeight(480);

   layouts->addWidget(start_widget);
   layouts->addWidget(newgame_widget);
   //layouts->addWidget(options_widget);
   layouts->setCurrentIndex(0);

   main_layout->addWidget(layouts);
   this->setLayout(main_layout);
}

MainMenu::~MainMenu()
{
}

void MainMenu::changeStackWidget(QWidget* caller)
{
    layouts->setCurrentIndex(layouts->indexOf(caller));
}

QWidget* MainMenu::getNewGame()
{
    return newgame_widget;
}

QWidget* MainMenu::getStart()
{
    return start_widget;
}
