#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent)
{
   main_layout = new QVBoxLayout();

   new_game_button = new QPushButton(QString("New Game"));
   continue_game_button = new QPushButton(QString("Continue Game"));
   options_button = new QPushButton(QString("Options"));
   exit_button = new QPushButton(QString("Exit"));

   main_layout->addWidget(new_game_button);
   main_layout->addWidget(continue_game_button);
   main_layout->addWidget(options_button);
   main_layout->addWidget(exit_button);

   this->setLayout(main_layout);
   this->setWindowTitle(QString("Main Menu"));

   QObject::connect(new_game_button, SIGNAL(clicked()), this, SLOT(new_game()));
   QObject::connect(continue_game_button, SIGNAL(clicked()), this, SLOT(continue_game()));
   QObject::connect(options_button, SIGNAL(clicked()), this, SLOT(options()));
   QObject::connect(exit_button, SIGNAL(clicked()), this, SLOT(exit()));
}

MainMenu::~MainMenu()
{
}

void MainMenu::new_game()
{
    qDebug() << "Add new_game functionality";
    // TODO: Add functionality
}

void MainMenu::continue_game()
{
    qDebug() << "Add continue_game functionality";
    // TODO: Add functionality
}

void MainMenu::options()
{
    qDebug() << "Add options functionality";
    // TODO: Add functionality
}

void MainMenu::exit()
{
    qDebug() << "Add exit functionality";
    // TODO: Add functionality

    this->close();
}

