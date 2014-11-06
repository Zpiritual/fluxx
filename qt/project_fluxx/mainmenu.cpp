#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent)
{
   main_widget = new QWidget();
   options_widget = new QWidget();
   main_layout = new QVBoxLayout();
   options_layout = new QVBoxLayout();
   new_game_button = new QPushButton(QString("New Game"));
   continue_game_button = new QPushButton(QString("Continue Game"));
   options_button = new QPushButton(QString("Options"));
   exit_button = new QPushButton(QString("Exit"));
   temp = new QVBoxLayout();

   main_layout->addWidget(new_game_button);
   main_layout->addWidget(continue_game_button);
   main_layout->addWidget(options_button);
   main_layout->addWidget(exit_button);


   options_layout->addWidget(exit_button);
   this->setWindowTitle(QString("Main Menu"));
   this->setMinimumWidth(640);
   this->setMinimumHeight(480);

   adjust_button_height(75);
   adjust_button_width(320);

   main_layout->setAlignment(new_game_button, Qt::AlignHCenter);
   main_layout->setAlignment(continue_game_button, Qt::AlignHCenter);
   main_layout->setAlignment(options_button, Qt::AlignHCenter);
   main_layout->setAlignment(exit_button, Qt::AlignHCenter);

   QObject::connect(new_game_button, SIGNAL(clicked()), this, SLOT(new_game()));
   QObject::connect(continue_game_button, SIGNAL(clicked()), this, SLOT(continue_game()));
   QObject::connect(options_button, SIGNAL(clicked()), this, SLOT(options()));
   QObject::connect(exit_button, SIGNAL(clicked()), this, SLOT(exit()));

   main_widget->setLayout(main_layout);
   options_widget->setLayout(options_layout);

   layouts = new QStackedWidget();
   layouts->addWidget(main_widget);
   layouts->addWidget(options_widget);

   layouts->setCurrentIndex(0);

   temp->addWidget(layouts);
   this->setLayout(temp);



}

MainMenu::~MainMenu()
{
}

void MainMenu::new_game()
{
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
}

void MainMenu::options()
{
    layouts->setCurrentIndex(1);
    qDebug() << "Add options functionality";
    // TODO: Add functionality
}

void MainMenu::exit()
{
    qDebug() << "Add exit functionality";
    // TODO: Add functionality

    this->close();
}

void MainMenu::adjust_button_height(int height)
{
    new_game_button->setMinimumHeight(height);
    new_game_button->setMaximumHeight(height);
    continue_game_button->setMinimumHeight(height);
    continue_game_button->setMaximumHeight(height);
    options_button->setMinimumHeight(height);
    options_button->setMaximumHeight(height);
    exit_button->setMinimumHeight(height);
    exit_button->setMaximumHeight(height);
}

void MainMenu::adjust_button_width(int width)
{
    new_game_button->setMinimumWidth(width);
    new_game_button->setMaximumWidth(width);
    continue_game_button->setMinimumWidth(width);
    continue_game_button->setMaximumWidth(width);
    options_button->setMinimumWidth(width);
    options_button->setMaximumWidth(width);
    exit_button->setMinimumWidth(width);
    exit_button->setMaximumWidth(width);
}
