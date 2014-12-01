#include "gui.h"
#include "BoardSnapshot.h"
 #include "cardidloop.h"

Gui::Gui(std::vector<ProfileName> players, QWidget *parent) :
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
    left_column = new QVBoxLayout();

    left_column->addWidget(trash_widget);
    left_column->addWidget(log_widget);

    mid_column_top->addWidget(deck_widget);
    mid_column_top->addWidget(goals_widget);

    mid_column->addLayout(mid_column_top);
    mid_column->addWidget(rules_widget);
    mid_column->addWidget(active_player_widget);

    mid_column->setAlignment(active_player_widget, Qt::AlignBottom);
    mid_column->setAlignment(mid_column_top, Qt::AlignTop|Qt::AlignCenter);

    this->setMinimumHeight(600);
    this->setMinimumWidth(1280);
    this->setWindowTitle(QString("Fluxx"));

    layout->addLayout(left_column);
    layout->addLayout(mid_column);
    layout->addWidget(player_list_widget);

    this->setLayout(layout);
}

Gui::~Gui(){
}

const PlayerID Gui::pickPlayer(const BoardSnapshot* const snapshot)
{
    update(snapshot);
    //return player_list_widget->pickPlayer();
}

//BoardSnapshot* snapshot
const CardID Gui::pickCard(const BoardSnapshot* const snapshot, const CardContainerID& containerid)
{
    update(snapshot);
    CardIdLoop loop;

    if(containerid == CardContainerID("Rules"))
    {
        rules_widget->setConnections(loop);
        qDebug() << "pickcard in gui";

        loop.exec();
    }
    else if(containerid == CardContainerID("Goals"))
    {
        goals_widget->setConnections(loop);
        loop.exec();
    }
    else if(containerid == CardContainerID("Trash"))
    {
        trash_widget->setConnections(loop);
     //   loop.exec();
    }
    else if(containerid == CardContainerID(snapshot->current_player.getString()+"_hand") ||
            containerid == CardContainerID("TempB") ||
            containerid == CardContainerID("tempA"))
    {
         active_player_widget->connectActiveHand(loop);
         loop.exec();
    }
    else if(containerid == CardContainerID(snapshot->current_player.getString()+"_keepers"))
    {
        active_player_widget->connectActiveKeepers(loop);
        loop.exec();
    }
    //Det är en spelares keepers men inte den aktiva spelarens keepers
//    else if(containerid.val.find("_hand") != std::string::npos &&
//            containerid.val.find(snapshot->current_player.getString()) != std::string::npos)
//        player_list_widget->connectKeepers(int(containerid.val.at(6)));
    //Det är en spelares hand men inte den aktiva spelarens hand.
//    else if(containerid.val.find("_hand") != std::string::npos &&
//            containerid.val.find(snapshot->current_player.getString() != std::string::npos))
//        player_list_widget->connectHand(int(containerid.val.at(6)));

 //   CardButton sentbutton = dynamic_cast<CardButton*>(loop.sender());
   // return sentbutton.getCardId().val;
    qDebug() << "pickcard in gui";
    return loop.getCardId();
    //
}


void Gui::nextPlayer()
{

}

void Gui::update(const BoardSnapshot* const snapshot) //Lägg till i alla klasser
{
    rules_widget->updateCards(snapshot->getContainer(CardContainerID("Rules")));
    //player_list_widget->updatePlayers(snapshot);
    trash_widget->updateCards(snapshot->getContainer(CardContainerID("Trash")));
    goals_widget->update(snapshot->getContainer(CardContainerID("Goals")));
    active_player_widget->update(snapshot);

    qDebug() << "update in gui";

}
