#include "start.h"

Start::Start(QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout();

    new_game_button = new QPushButton(QString("New Game"));
    continue_game_button = new QPushButton(QString("Continue Game"));
    options_button = new QPushButton(QString("Options"));
    exit_button = new QPushButton(QString("Exit"));

    layout->addWidget(new_game_button);
    layout->addWidget(continue_game_button);
    layout->addWidget(options_button);
    layout->addWidget(exit_button);

    adjust_button_height(75);
    adjust_button_width(320);

    layout->setAlignment(new_game_button, Qt::AlignHCenter);
    layout->setAlignment(continue_game_button, Qt::AlignHCenter);
    layout->setAlignment(options_button, Qt::AlignHCenter);
    layout->setAlignment(exit_button, Qt::AlignHCenter);

    QObject::connect(new_game_button, SIGNAL(clicked()), this, SLOT(new_game()));
    QObject::connect(continue_game_button, SIGNAL(clicked()), this, SLOT(continue_game()));
    QObject::connect(options_button, SIGNAL(clicked()), this, SLOT(options()));
    QObject::connect(exit_button, SIGNAL(clicked()), this, SLOT(exit()));

    parent2 = dynamic_cast<MainMenu*>(parent);
    this->setLayout(layout);
}


Start::~Start()
{
}

void Start::new_game()
{
   // parent2->hideWidgets();
    parent2->newGame();
    qDebug() << "Add new_game functionality";
    // TODO: Add functionality
}

void Start::continue_game()
{
    qDebug() << "Add continue_game functionality";
    // TODO: Add functionality
}

void Start::options()
{
    //parent2->options();
    qDebug() << "Add options functionality";
    // TODO: Add functionality
}

void Start::exit()
{
    qDebug() << "Add exit functionality";
    // TODO: Add functionality

    this->close();
}



void Start::adjust_button_height(int height)
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

void Start::adjust_button_width(int width)
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
