#include "gui.h"

Gui::Gui(std::vector<PlayerID> players, QWidget *parent) :
    QWidget(parent)
{
    player_ids = players;

    layout = new QHBoxLayout();
    log_widget = new LogWidget(this);
    player_list_widget = new PlayerList(this);
    rules_widget = new RulesGridWidget(this);
    active_player_widget = new ActivePlayer(this);
    mid_column = new QVBoxLayout();



    mid_column->addWidget(rules_widget);
    mid_column->addWidget(active_player_widget);

    mid_column->setAlignment(active_player_widget, Qt::AlignBottom);

    this->setMinimumHeight(600);
    this->setMinimumWidth(1280);
    this->setWindowTitle(QString("Fluxx"));

    layout->addWidget(log_widget);
    layout->addLayout(mid_column);
    layout->addWidget(player_list_widget);

    layout->setAlignment(log_widget, Qt::AlignLeft);

    this->setLayout(layout);
}

Gui::~Gui(){
}

const PlayerID Gui::pickPlayer(const BoardSnapshot snapshot)
{
    //update(snapshot);
    //return player_list_widget->pickPlayer();
}

const CardID Gui::pickCard(BoardSnapshot snapshot, ContainerID containerid)
{

}

void Gui::nextPlayer()
{

}

void Gui::update(BoardSnapshot snapshot) //Lägg till i alla klasser
{

}
