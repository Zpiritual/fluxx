#include "gui.h"

Gui::Gui(std::vector<ProfileName> players, QWidget *parent) :
    QWidget(parent)
{
    player_ids = players;
    uiElements();
}

Gui::~Gui()
{
    delete card_id_loop;
    delete player_loop;
    delete event_loop;
    delete trash_widget;
    delete log_widget;
    delete left_column;
    delete deck_widget;
    delete goals_widget;
    delete mid_column_right;
    delete rules_widget;
    delete active_player_widget;
    delete mid_column;
    delete player_list_widget;
    delete layout;
}

PlayerID Gui::pickPlayer(const BoardSnapshot* const snapshot)
{
    qDebug() << "Pick Player: ";
    update(snapshot, false);
    player_loop = new PlayerLoop{};
    player_list_widget->setConnections(*player_loop);
    player_loop->exec();

    if (player_list_widget->getPlayerId(player_loop->getPlayerName()) == snapshot->current_player)
    {
        message(QString("Pick Player"), QString("Can't pick yourself! Pick another player please."));
        pickPlayer(snapshot);
    }

    PlayerID tempid = player_list_widget->getPlayerId(player_loop->getPlayerName());
    return tempid;
}

//BoardSnapshot* snapshot
CardID Gui::pickCard(const BoardSnapshot* const snapshot)
{
    update(snapshot, false);

    if(snapshot->active_player != snapshot->current_player)
    {
        event_loop = new QEventLoop();
        active_player_widget->changePlayer(player_ids.at(snapshot->active_player.getInt()-1), *event_loop);

        delete event_loop;
        update(snapshot, true);
    }

    card_id_loop = new CardIdLoop;

    if(snapshot->target_container.val == "Rules")
    {
        rules_widget->setConnections(*card_id_loop);
        card_id_loop->exec();
    }
    else if(snapshot->target_container.val == "Goal")
    {
        goals_widget->setConnections(*card_id_loop); 
    }
    else if(snapshot->target_container.val == "Trash")
    {
        trash_widget->setConnections(*card_id_loop);
    }
    else if(snapshot->target_container == CardContainerID(snapshot->active_player.getString()+"_hand") ||
            snapshot->target_container == CardContainerID("tempB") ||
            snapshot->target_container == CardContainerID("tempA"))
    {
         active_player_widget->connectActiveHand(*card_id_loop);
         card_id_loop->exec();
    }
    else if(snapshot->target_container.val == (snapshot->active_player.getString()+"_keepers"))
    {
        active_player_widget->connectActiveKeepers(*card_id_loop);
        card_id_loop->exec();
    }
    //Det är en spelares keepers men inte den aktiva spelarens keepers
    else if(((snapshot->target_container.val.find("_hand") != std::string::npos) ||
            (snapshot->target_container.val.find("_keepers") != std::string::npos)) &&
            snapshot->target_container.val.find(snapshot->active_player.getString()) == std::string::npos)
    {
        BigCardCollection* bigcollection = new BigCardCollection(snapshot->getContainer(snapshot->target_container).getCards(),*card_id_loop);
        bigcollection->show();
        card_id_loop->exec();
        bigcollection->close();
    }

    qDebug() << "You picked card: " + QString::number(card_id_loop->getCardId().val);
    return card_id_loop->getCardId();
}

void Gui::nextPlayer(const BoardSnapshot* const snapshot)
{
    update(snapshot, false);
    event_loop = new QEventLoop();

    if(snapshot->direction == Direction::CLOCKWISE)
    {
        active_player_widget->endTurn(player_ids.at(snapshot->current_player.getInt() % player_ids.size()), *event_loop);
    }
    else
    {
        if((snapshot->current_player.getInt() - 1) == 0)
        {
            active_player_widget->endTurn(player_ids.at(player_ids.size() - 1), *event_loop);
        }
        else
        {
            active_player_widget->endTurn(player_ids.at(snapshot->current_player.getInt() - 2),*event_loop);
        }
    }
    delete event_loop;
}

Direction Gui::chooseDirection(const BoardSnapshot* const snapshot)
{
    update(snapshot, false);
    QMessageBox directionpicker;
    directionpicker.setText(QString("Choose a direction"));
    QAbstractButton *clockwise = directionpicker.addButton(QString("Clockwise"),QMessageBox::YesRole);
    directionpicker.addButton(QString("Anticlockwise"), QMessageBox::NoRole);
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
    // TODO: Stop evenloops
    this->hide();

//    event_loop->exit();
//    card_id_loop->exit();
//    player_loop->exit();

//    if(event_loop->isRunning())
//        event_loop->quit();
//    if(card_id_loop->isRunning())
//        card_id_loop->quit();
//    if(player_loop->isRunning())
//        player_loop->quit();

    qDebug() << "Closing window";

    event->accept();
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
    log_widget = new LogWidget(player_ids, this);
    player_list_widget = new PlayerList(player_ids, this);
    deck_widget = new DeckButton(this);
    trash_widget = new TrashButton(this);
    goals_widget = new GoalButtons(this);
    rules_widget = new RulesGridWidget(this);
    active_player_widget = new ActivePlayer(this);
    mid_column = new QVBoxLayout();
    mid_column_right = new QVBoxLayout();
    left_column = new QVBoxLayout();
    rules_goals_row = new QHBoxLayout();
    rules_scroll = new QScrollArea();

    this->setAutoFillBackground(true);
    this->setPalette(Qt::white);
    left_column->addWidget(trash_widget);
    left_column->addWidget(log_widget);

    mid_column_right->addWidget(deck_widget);
    mid_column_right->addWidget(goals_widget);
    mid_column_right->setAlignment(deck_widget, Qt::AlignRight | Qt::AlignTop);
    mid_column_right->setAlignment(goals_widget, Qt::AlignTrailing);

    rules_scroll->setWidget(rules_widget);
    rules_scroll->setFrameStyle(QFrame::NoFrame);

    rules_goals_row->addWidget(rules_scroll);
    rules_goals_row->addLayout(mid_column_right);

    mid_column->addLayout(rules_goals_row);
    mid_column->addWidget(active_player_widget);

    rules_goals_row->setAlignment(rules_widget, Qt::AlignTop);
    mid_column->setAlignment(active_player_widget, Qt::AlignTop);
    rules_goals_row->setAlignment(mid_column_right, Qt::AlignRight|Qt::AlignTop);

    this->setMinimumHeight(600);
    this->setMinimumWidth(1280);
    this->showMaximized();
    this->setWindowTitle(QString("Fluxx"));

//    rules_widget->setMinimumHeight(270);
//    goals_widget->setMinimumSize(100,280);
    //mid_column_right->setAlignment(goals_widget, Qt::AlignTop);

    layout->addLayout(left_column);
    layout->addLayout(mid_column);
    layout->addWidget(player_list_widget);

    this->setLayout(layout);
}

void Gui::update(const BoardSnapshot* const snapshot, const bool changed_player) //Lägg till i alla klasser
{
    rules_widget->updateCards(snapshot->getContainer(CardContainerID("Rules")));
    player_list_widget->updatePlayers(snapshot);
    trash_widget->updateCards(snapshot->getContainer(CardContainerID("Trash")));
    goals_widget->updateCards(snapshot->getContainer(CardContainerID("Goal")));
    active_player_widget->updateCards(snapshot, changed_player);
    log_widget->updateLog(snapshot);

}
