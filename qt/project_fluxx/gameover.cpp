#include "gameover.h"

GameOver::GameOver(SessionData session_data, std::vector<ProfileName> players, QWidget *parent) :
    QWidget(parent)
{
    parent2 = dynamic_cast<MainMenu*>(parent);
    uiElementSetup(session_data, players);
    connectSignals();
}

void GameOver::uiElementSetup(SessionData session_data,std::vector<ProfileName> players)
{
    layout = new QVBoxLayout;
    ok_button = new QPushButton("Return to main menu");
    winning_player_label = new QLabel(QString("Congratulations ") + QString::fromStdString(players.at(session_data.winning_player.getInt()-1).val)+ QString(" has won!"));

    layout->addWidget(winning_player_label);
    layout->addWidget(ok_button);

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

