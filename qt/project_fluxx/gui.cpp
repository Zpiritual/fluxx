#include "gui.h"

Gui::Gui(std::vector<ProfileName> players, QWidget *parent) :
    QWidget(parent)
{
    player_ids = players;
    uiElements();
}

Gui::~Gui()
{
    delete trash_widget;
    delete log_widget;
    delete left_column;
    delete deck_widget;
    delete goals_widget;
    delete mid_column_top;
    delete rules_widget;
    delete active_player_widget;
    delete mid_column;
    delete player_list_widget;
    delete layout;
}

const PlayerID Gui::pickPlayer(const BoardSnapshot* const snapshot)
{
    qDebug() << "Pick Player: ";
    update(snapshot);
    PlayerLoop loop;
    player_list_widget->setConnections(loop);
    loop.exec();

    if (player_list_widget->getPlayerId(loop.getPlayerName()) == snapshot->current_player)
    {
        message(QString("Pick Player"), QString("Can't pick yourself! Pick another player please."));
        pickPlayer(snapshot);
    }

    return player_list_widget->getPlayerId(loop.getPlayerName());
}

//BoardSnapshot* snapshot
const CardID Gui::pickCard(const BoardSnapshot* const snapshot, const CardContainerID containerid)
{
    update(snapshot);

    CardIdLoop loop;

    if(containerid == CardContainerID("Rules"))
    {
        rules_widget->setConnections(loop);
        qDebug() << "pickcard rules in gui";

        loop.exec();
    }
    else if(containerid == CardContainerID("Goals"))
    {
        goals_widget->setConnections(loop);
        qDebug() << "pickcard goals in gui";
        loop.exec();
    }
    else if(containerid == CardContainerID("Trash"))
    {
        qDebug() << "pickcard trash in gui";
        trash_widget->setConnections(loop);
     //   loop.exec();
    }
    else if(containerid == CardContainerID(snapshot->current_player.getString()+"_hand") ||
            containerid == CardContainerID("TempB") ||
            containerid == CardContainerID("tempA"))
    {
         active_player_widget->connectActiveHand(loop);
         qDebug() << "pick active hand in gui";
         loop.exec();
    }
    else if(containerid == CardContainerID(snapshot->current_player.getString()+"_keepers"))
    {
        active_player_widget->connectActiveKeepers(loop);
        loop.exec();
    }
    //Det är en spelares keepers men inte den aktiva spelarens keepers
    else if(((containerid.val.find("_hand") != std::string::npos) ||
            (containerid.val.find("_keepers") != std::string::npos)) &&
            containerid.val.find(snapshot->current_player.getString()) != std::string::npos)
    {
        BigCardCollection* bigcollection = new BigCardCollection(snapshot->getContainer(containerid).getCards(),loop);
        bigcollection->show();
        loop.exec();
        bigcollection->close();
        delete bigcollection;
    }

    qDebug() << "You picked card: " + QString::number(loop.getCardId().val);
    return loop.getCardId();
}

const CardID Gui::pickCard(const BoardSnapshot* const snapshot, const CardContainerID containerid, const PlayerID)
{
    update(snapshot);

    CardIdLoop loop;

    if(containerid == CardContainerID("Rules"))
    {
        rules_widget->setConnections(loop);
        qDebug() << "pickcard rules in gui";

        loop.exec();
    }
    else if(containerid == CardContainerID("Goals"))
    {
        goals_widget->setConnections(loop);
        qDebug() << "pickcard goals in gui";
        loop.exec();
    }
    else if(containerid == CardContainerID("Trash"))
    {
        qDebug() << "pickcard trash in gui";
        trash_widget->setConnections(loop);
     //   loop.exec();
    }
    else if(containerid == CardContainerID(snapshot->current_player.getString()+"_hand") ||
            containerid == CardContainerID("TempB") ||
            containerid == CardContainerID("tempA"))
    {
         active_player_widget->connectActiveHand(loop);
         qDebug() << "pick active hand in gui";
         loop.exec();
    }
    else if(containerid == CardContainerID(snapshot->current_player.getString()+"_keepers"))
    {
        active_player_widget->connectActiveKeepers(loop);
        loop.exec();
    }
    //Det är en spelares keepers men inte den aktiva spelarens keepers
    else if(((containerid.val.find("_hand") != std::string::npos) ||
            (containerid.val.find("_keepers") != std::string::npos)) &&
            containerid.val.find(snapshot->current_player.getString()) != std::string::npos)
    {
        BigCardCollection* bigcollection = new BigCardCollection(snapshot->getContainer(containerid).getCards(),loop);
        bigcollection->show();
        loop.exec();
        bigcollection->close();
        delete bigcollection;
    }

    qDebug() << "You picked card: " + QString::number(loop.getCardId().val);
    return loop.getCardId();
    //
}

void Gui::nextPlayer(const BoardSnapshot* const snapshot)
{
    update(snapshot);

    if(snapshot->direction == Direction::CLOCKWISE)
    {
        active_player_widget->switchPlayer(player_ids.at(snapshot->current_player.getInt() % player_ids.size()));
    }
    else
    {
        if((snapshot->current_player.getInt() - 1) == 0)
        {
            active_player_widget->switchPlayer(player_ids.at(player_ids.size() - 1));
        }
        else
        {
            active_player_widget->switchPlayer(player_ids.at(snapshot->current_player.getInt() - 2));
        }
    }
}

const Direction Gui::chooseDirection(const BoardSnapshot* const snapshot)
{
    update(snapshot);
    QMessageBox directionpicker;
    directionpicker.setText(QString("Choose a direction"));
    QAbstractButton *clockwise = directionpicker.addButton(QString("Clockwise"),QMessageBox::YesRole);
    QAbstractButton* anticlockwise = directionpicker.addButton(QString("Anticlockwise"), QMessageBox::NoRole);
    directionpicker.exec();
    if (directionpicker.clickedButton() == clockwise ) {
        qDebug() << "You picked clockwise";
        return Direction::CLOCKWISE;

    } else {
        qDebug() << "You picked counterclockwise";
        return Direction::COUNTERCLOCKWISE;
    }
}

void Gui::closeEvent(QCloseEvent* event)
{
    event->accept();
    delete this;
}

void Gui::message(const QString& title, const QString& message) const
{
    // Display a message box
    QMessageBox message_dialog;
    message_dialog.setWindowTitle(title);
    message_dialog.setText(message);
    message_dialog.exec();
}

void Gui::uiElements()
{
    layout = new QHBoxLayout();
    log_widget = new LogWidget(this);
    player_list_widget = new PlayerList(player_ids, this);
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

void Gui::update(const BoardSnapshot* const snapshot) //Lägg till i alla klasser
{
    rules_widget->updateCards(snapshot->getContainer(CardContainerID("Rules")));
    player_list_widget->updatePlayers(snapshot);
    trash_widget->updateCards(snapshot->getContainer(CardContainerID("Trash")));
    goals_widget->updateCards(snapshot->getContainer(CardContainerID("Goal")));
    active_player_widget->updateCards(snapshot);
    log_widget->update(snapshot);

    qDebug() << "update in gui";
}
