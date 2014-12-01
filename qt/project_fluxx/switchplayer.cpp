#include "switchplayer.h"

SwitchPlayer::SwitchPlayer(const ProfileName& next_player, QEventLoop& loop, QWidget *parent) :
    QWidget(parent)
{
    uiElements(next_player);
    connectSignals(loop);
}

void SwitchPlayer::uiElements(const ProfileName& next_player)
{
    main_layout = new QHBoxLayout();
    next_player_layout = new QVBoxLayout();

    next_player_button = new QPushButton(QString{"Next Player"});
    next_player_text = new QLabel();

    next_player_text->setText(QString("NextPlayer: ") + QString::fromStdString(next_player.val));
    next_player_text->setMinimumHeight(30);

    next_player_button->setMinimumWidth(100);
    next_player_button->setMinimumHeight(75);
    this->setMinimumHeight(259);
    this->setMinimumWidth(500);
    next_player_layout->addWidget(next_player_text);
    next_player_layout->addWidget(next_player_button);

    main_layout->addLayout(next_player_layout);

    main_layout->setAlignment(next_player_layout, Qt::AlignTop);
    next_player_layout->setAlignment(next_player_text, Qt::AlignTop);
    next_player_layout->setAlignment(next_player_button, Qt::AlignTop);

    this->setLayout(main_layout);
}

void SwitchPlayer::connectSignals(QEventLoop& loop)
{
    QObject::connect(next_player_button, SIGNAL(clicked()), &loop, SLOT(quit()));
}

void SwitchPlayer::nextPlayer()
{
    qDebug() << "Next Player Functionality";
    // TODO: Add next player functionality
    // Switch player and enter gameboard
}
