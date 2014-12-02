#include "start.h"

Start::Start(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
    parent2 = dynamic_cast<MainMenu*>(parent);
}


Start::~Start()
{
    delete continue_game_button;
    delete new_game_button;
    delete options_button;
    delete exit_button;
    delete layout;
}

void Start::new_game()
{
   // parent2->hideWidgets();
    if(parent2 != nullptr)
    {
        parent2->newGame();
    }
    else
    {
        message(QString("Error"), QString("parent2 does not exist"));
    }
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
    if(parent2 != nullptr)
    {
        parent2->options();
    }
    else
    {
        message(QString("Error"), QString("parent2 does not exist"));
    }
    qDebug() << "Add options functionality";
    // TODO: Add functionality
}

void Start::exit()
{
    qDebug() << "Add exit functionality";
    // TODO: Add functionality

    if(parent2 != nullptr)
    {
        parent2->writeProfilesToFile();
        //parent2->close();
        delete parent2;
    }
    else
    {
        message(QString("Error"), QString("parent2 does not exist"));
    }
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

void Start::connectSignals()
{
    QObject::connect(new_game_button, SIGNAL(clicked()), this, SLOT(new_game()));
    QObject::connect(continue_game_button, SIGNAL(clicked()), this, SLOT(continue_game()));
    QObject::connect(options_button, SIGNAL(clicked()), this, SLOT(options()));
    QObject::connect(exit_button, SIGNAL(clicked()), this, SLOT(exit()));
}

void Start::uiElements()
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

    connectSignals();

    this->setLayout(layout);
}

void Start::message(const QString& title, const QString& message) const
{
    // Display a message box
    QMessageBox message_dialog;
    message_dialog.setWindowTitle(title);
    message_dialog.setText(message);
    message_dialog.exec();
}
