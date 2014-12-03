#include "switchplayer.h"

SwitchPlayer::SwitchPlayer(const ProfileName& next_player, QEventLoop& loop, const bool end_turn, QWidget *parent) :
    QWidget(parent)
{
    uiElements(next_player, end_turn);
    connectSignals(loop);
}

SwitchPlayer::~SwitchPlayer()
{
    delete next_player_button;
    delete next_player_text;
    delete next_player_layout;
    delete main_layout;
}

void SwitchPlayer::uiElements(const ProfileName& next_player, const bool end_turn)
{
    main_layout = new QHBoxLayout();
    next_player_layout = new QVBoxLayout();
    if(end_turn)
        next_player_button = new QPushButton(QString{"Next Player:"} + QString::fromStdString(next_player.val));
    else
        next_player_button = new QPushButton(QString{"Change to player:"} + QString::fromStdString(next_player.val));
    next_player_text = new QLabel();

    if(end_turn)
        next_player_text->setText(QString("Your turn is over"));
    else
        next_player_text->setText(QString("Another player need to pick card(s)") + QString::fromStdString(next_player.val));

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
