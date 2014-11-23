#include "switchplayer.h"

SwitchPlayer::SwitchPlayer(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
    connectSignals();
}

void SwitchPlayer::uiElements()
{
    main_layout = new QHBoxLayout();
    next_player_layout = new QVBoxLayout();
    new_player_layout = new QVBoxLayout();

    next_player_button = new QPushButton(QString{"Next Player"});
    new_player_button = new QPushButton(QString{"New Player"});
    name_field = new QLineEdit();
    next_player_text = new QLabel();

    next_player_text->setText(QString{"NextPlayer: "} + QString{"namn"} + QString{" Previous Player: "} + QString{"namn"});
    next_player_text->setMinimumHeight(30);

    new_player_button->setEnabled(false);
    next_player_button->setMinimumWidth(320);
    next_player_button->setMinimumHeight(75);
    new_player_button->setMinimumWidth(320);
    new_player_button->setMinimumHeight(75);
    name_field->setMaximumWidth(75);

    next_player_layout->addWidget(next_player_text);
    next_player_layout->addWidget(next_player_button);
    new_player_layout->addWidget(name_field);
    new_player_layout->addWidget(new_player_button);
    main_layout->addLayout(next_player_layout);
    main_layout->addLayout(new_player_layout);

    main_layout->setAlignment(next_player_layout, Qt::AlignLeft);
    main_layout->setAlignment(new_player_layout, Qt::AlignRight);
    next_player_layout->setAlignment(next_player_text, Qt::AlignBottom);
    next_player_layout->setAlignment(next_player_button, Qt::AlignTop);
    new_player_layout->setAlignment(new_player_button, Qt::AlignTop);
    new_player_layout->setAlignment(name_field, Qt::AlignBottom);

    this->setMinimumWidth(640);
    this->setMinimumHeight(480);
    this->setWindowTitle(QString{"Next Player"});
    this->setLayout(main_layout);
}

void SwitchPlayer::connectSignals()
{
    QObject::connect(name_field, SIGNAL(textChanged(QString)), this, SLOT(enableNewPlayerButton()));
    QObject::connect(next_player_button, SIGNAL(clicked()), this, SLOT(nextPlayer()));
    QObject::connect(new_player_button, SIGNAL(clicked()), this, SLOT(newPlayer()));
}

void SwitchPlayer::enableNewPlayerButton()
{
    if(name_field->text() == "")
    {
        new_player_button->setEnabled(false);
    }
    else
    {
        new_player_button->setEnabled(true);
    }
}

void SwitchPlayer::nextPlayer()
{
    qDebug() << "Next Player Functionality";
    // TODO: Add next player functionality
    // Switch player and enter gameboard
}

void SwitchPlayer::newPlayer()
{
    qDebug() << "New Player Functionality";
    // TODO:: Add new player functionality
    // Add new player and enter gameboard with new player as current player

}
