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
<<<<<<< HEAD
    qDebug() << "Add new_game functionality";
    // TODO: Add functionality
    main_layout->addWidget(exit_button);
    main_layout->setAlignment(exit_button, Qt::AlignHCenter);
    main_layout->update();
    exit_button->show();
}

void MainMenu::continue_game()
{
    qDebug() << "Add continue_game functionality";
    // TODO: Add functionality
    main_layout->removeWidget(exit_button);
    main_layout->update();
    exit_button->hide();
=======
    newgame_widget = new NewGame(this);
    main_layout->addWidget(newgame_widget);
    main_layout->removeWidget(start_widget);

    delete start_widget;
>>>>>>> fluxx/Main_Menu_Prototype
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
