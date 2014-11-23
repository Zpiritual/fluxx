#include "gui.h"

Gui::Gui(std::vector<PlayerID> players, QWidget *parent) :
    QWidget(parent)
{
    player_ids = players;

    layout = new QHBoxLayout();
    log_widget = new LogWidget(this);
    player_list_widget = new PlayerList(players, this);
    deck_widget = new DeckButton(this);
    trash_widget = new TrashButton(this);
    goals_widget = new GoalButtons(this);
    rules_widget = new RulesGridWidget(this);
    active_player_widget = new ActivePlayer(this);
    mid_column = new QVBoxLayout();
    mid_column_top = new QHBoxLayout();

    mid_column_top->addWidget(deck_widget);
    mid_column_top->addWidget(trash_widget);
    mid_column_top->addWidget(goals_widget);

    mid_column->addLayout(mid_column_top);
    mid_column->addWidget(rules_widget);
    mid_column->addWidget(active_player_widget);

    mid_column->setAlignment(active_player_widget, Qt::AlignBottom);
    mid_column->setAlignment(mid_column_top, Qt::AlignTop|Qt::AlignCenter);

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
    //update(snapshot);

}

void Gui::nextPlayer()
{

}

void Gui::update(const BoardSnapshot& snapshot) //Lägg till i alla klasser
{

    //rules_widget->updateCards(snapshot.getContainer(ContainerID("Rules")));


}
