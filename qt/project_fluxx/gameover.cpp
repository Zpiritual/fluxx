#include "gameover.h"

GameOver::GameOver(SessionData session_data, std::vector<ProfileName> players, QWidget *parent) :
    QWidget(parent)
{
    parent2 = dynamic_cast<MainMenu*>(parent);
    uiElementSetup(session_data, players);
    connectSignals();
}

GameOver::~GameOver()
{
    delete ok_button;
    delete winning_player_label;
    delete time_played_label;
    delete layout;
}

void GameOver::uiElementSetup(SessionData session_data,std::vector<ProfileName> players)
{
    layout = new QVBoxLayout;
    ok_button = new QPushButton("Return to main menu");
    winning_player_label = new QLabel(QString("Congratulations ") + QString::fromStdString(players.at(session_data.winning_player.getInt()-1).val)+ QString(" has won!"));
    time_played_label = new QLabel(QString("Time played: ") + QString::number(session_data.elapsed_time/60) + QString(":") + QString::number(session_data.elapsed_time%60));
    stats_label = new QLabel;

    layout->addWidget(winning_player_label);
    layout->addWidget(time_played_label);
    layout->addWidget(stats_label);
    layout->addWidget(ok_button);

    layout->setAlignment(winning_player_label, Qt::AlignCenter);
    layout->setAlignment(time_played_label, Qt::AlignCenter);
    layout->setAlignment(stats_label, Qt::AlignCenter);

    for(const PlayerStats stat_item : session_data.players)
    {
        stats_label->setText(stats_label->text() + QString::fromStdString(players.at(stat_item._id.getInt()-1).val) + QString("\n"));
        stats_label->setText(stats_label->text() + QString("Maximum number of cards played consecutively: ") + QString::number(stat_item._max_consecutive_plays) + QString("cards\n"));
        stats_label->setText(stats_label->text() + QString("Number of cards drawn and played: " + QString::number(stat_item._total_drawn_cards) + " cards drawn and " + QString::number(stat_item._total_played_cards) + " cards played. \n"));
    }

    stats_label->setAlignment(Qt::AlignCenter);

    this->setLayout(layout);
}

void GameOver::connectSignals()
{
    QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(returnToMainMenu()));
}

void GameOver::returnToMainMenu()
{
    if(parent2 != NULL)
        parent2-> gameOverBack();
    else
    {
        qDebug() << "Error, parent2 does not exist in returnToMainMenu in gameover";
    }
}

