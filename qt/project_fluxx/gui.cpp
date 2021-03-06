#include "gui.h"

Gui::Gui(std::vector<ProfileName> players, MainMenu* main_menu, QWidget *parent) :
    QWidget(parent)
{
    player_ids = players;
    _parent = main_menu;
    qDebug() << "postparent in Gui";

    card_id_loop = NULL;
    player_loop = NULL;
    event_loop = NULL;

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
    delete active_hand;
    delete active_keepers;
    delete scroll_area_rules;
    delete scroll_area_hand;
    delete scroll_area_keepers;
    delete rules_keepers_column;
    delete mid_column;
    delete player_list_widget;
    delete layout;
}

PlayerID Gui::pickPlayer(const BoardSnapshot* const snapshot)
{
    update(snapshot, false);

    do
    {
        delete player_loop;
        player_loop = new PlayerLoop{};
        player_list_widget->setConnections(*player_loop);

        player_loop->exec();

        if (player_list_widget->getPlayerId(player_loop->getPlayerName()) == snapshot->current_player)
        {
            QMessageBox message_dialog;
            message_dialog.setWindowTitle("Pick Player");
            message_dialog.setText("Can't pick yourself! Pick another player please.");
            message_dialog.exec();

        }
    }while(player_list_widget->getPlayerId(player_loop->getPlayerName()) == snapshot->current_player);

    PlayerID tempid = player_list_widget->getPlayerId(player_loop->getPlayerName());

    delete player_loop;
    player_loop = NULL;

    return tempid;    
}

//BoardSnapshot* snapshot
CardID Gui::pickCard(const BoardSnapshot* const snapshot)
{
    qDebug() << "Entering pick card in gui";
    if(snapshot->active_player != previous_active_player && snapshot->current_player != snapshot->active_player)
    {
        previous_active_player = snapshot->active_player;
        event_loop = new QEventLoop();
        changePlayer(player_ids.at(snapshot->active_player.getInt()-1), *event_loop);

        delete event_loop;
        event_loop = NULL;
        update(snapshot, true);
    }
    else if(snapshot->current_player == snapshot->active_player)
    {
        previous_active_player = snapshot->active_player;
        update(snapshot, false);
    }
    else
        update(snapshot, true);

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
            snapshot->target_container == CardContainerID("tempA"))
    {
         connectActiveHand(*card_id_loop);
         card_id_loop->exec();
    }
    else if(snapshot->target_container.val == (snapshot->active_player.getString()+"_keepers"))
    {
        connectActiveKeepers(*card_id_loop);
        card_id_loop->exec();
    }
    //Det är en spelares keepers men inte den aktiva spelarens keepers
    else if(((snapshot->target_container.val.find("_hand") != std::string::npos) ||
            (snapshot->target_container.val.find("_keepers") != std::string::npos)) &&
            snapshot->target_container.val.find(snapshot->active_player.getString()) == std::string::npos)
    {
        BigCardCollection* bigcollection = new BigCardCollection(snapshot->getContainer(snapshot->target_container).getCards(),*card_id_loop, this);
        bigcollection->setWindowTitle(QString::fromStdString(snapshot->getContainer(snapshot->target_container).getID().val));
        bigcollection->show();
        card_id_loop->exec();
        bigcollection->close();
    }

    qDebug() << "You picked card: " + QString::number(card_id_loop->getCardId().val);
    CardID card_id= card_id_loop->getCardId();
    delete card_id_loop;
    card_id_loop = NULL;
    return card_id;
}

void Gui::nextPlayer(const BoardSnapshot* const snapshot)
{
    update(snapshot, false);
    event_loop = new QEventLoop();

    endTurn(player_ids.at(snapshot->next_player.getInt()-1),*event_loop);
    delete event_loop;
    event_loop = NULL;
    qDebug() << "exiting nextPlayer";
}

//Popup giving the player two choices, left button returns true, right false
bool Gui::playerDecision(const BoardSnapshot * const snapshot, const std::string& question, const std::string& left_button_text, const std::string& right_button_text)
{
    update(snapshot, false);
    QMessageBox questionbox;

    //Set window properties, always on top, no close button etc.
    questionbox.setText(QString::fromStdString(question));
    questionbox.setWindowFlags(((questionbox.windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint) & ~Qt::WindowCloseButtonHint));
    questionbox.raise();    //Raise above every other window

    //Add Buttons
    questionbox.addButton(QString::fromStdString(right_button_text), QMessageBox::NoRole);
    QAbstractButton *left_button= questionbox.addButton(QString::fromStdString(left_button_text),QMessageBox::YesRole);

    questionbox.exec();

    if (questionbox.clickedButton() == left_button) //Left button returns a true value from the function
        return true;
    else
        return false;
}

//If the player tries to close the gui window by clicking the x in the menu bar, alt+F4 or similar.
void Gui::closeEvent(QCloseEvent* event)
{
    //Create a message box asking the player if (s)he really want to close the game.
    QMessageBox message;
    message.setWindowTitle("Exit game?");
    message.setWindowFlags(message.windowFlags() | Qt::WindowStaysOnTopHint);
    message.setText("Are you sure you want to quit? All progress will be lost.");
    message.raise();
    QAbstractButton *yes_button= message.addButton(QString("Yes"),QMessageBox::YesRole);
    message.addButton("No",QMessageBox::NoRole);
    message.exec();

    if(message.clickedButton() == yes_button)
    {
        _parent->show(); //Show the main menu, needs to be done before the below line or entire program will exit.
        this->hide();
        if(card_id_loop != NULL)
            card_id_loop->exit();
        if(player_loop != NULL)
            player_loop->exit();
        if(event_loop != NULL)
            event_loop->exit();
        event->accept();
    }
    else
        event->ignore();
}

//Updates the content of everywidget
void Gui::update(const BoardSnapshot* const snapshot, const bool changed_player) //Lägg till i alla klasser
{
    rules_widget->updateCards(snapshot->getContainer(CardContainerID("Rules")));
    player_list_widget->updatePlayers(snapshot);
    trash_widget->updateCards(snapshot->getContainer(CardContainerID("Trash")));
    goals_widget->updateCards(snapshot->getContainer(CardContainerID("Goal")));
    log_widget->updateLog(snapshot);
    updateActiveHandAndKeepers(snapshot, changed_player);
}

//Helper function that updates the active hand and active keepers based on which player is active
void Gui::updateActiveHandAndKeepers(const BoardSnapshot* const snapshot, const bool changed_player)
{
    //Removes background colors getting stuck when hand shrinks
    active_hand->hide();
    active_hand->show();

    if(!changed_player)
    {
        if(snapshot->getContainer(CardContainerID("tempA")).getSize() != 0) //If there is a temporary hand, show that instead of regular hand
            active_hand->updateCards(snapshot->getContainer(CardContainerID("tempA")));
        else
            active_hand->updateCards(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_hand")));

        active_keepers->updateCards(snapshot->getContainer(CardContainerID(snapshot->current_player.getString()+"_keepers")));
    }
    else
    {
        active_hand->updateCards(snapshot->getContainer(snapshot->active_player.getString()+"_hand"));
        active_keepers->updateCards(snapshot->getContainer(snapshot->active_player.getString()+"_keepers"));
    }
}

//Enable clicking on the active keepers buttons
void Gui::connectActiveKeepers(CardIdLoop& loop)
{
    active_keepers->connectButtons(loop);
}

//Enable clicking on the active hand buttons
void Gui::connectActiveHand(CardIdLoop& loop)
{
    active_hand->connectButtons(loop);
}

//A player's turn is over, hide hand and switch player
void Gui::endTurn(const ProfileName& next_player, QEventLoop& loop)
{
    SwitchPlayer* switch_player = new SwitchPlayer(next_player, loop, true);

    scroll_area_hand->hide();
    mid_column->addWidget(switch_player);
    switch_player->setMinimumHeight(scroll_area_hand->sizeHint().height());

    loop.exec();

    mid_column->removeWidget(switch_player);
    delete switch_player;
    scroll_area_hand->show();
}

//The turn isn't over but another player has to choose cards to trash or similar.
void Gui::changePlayer(const ProfileName& next_player, QEventLoop& loop)
{
    SwitchPlayer* change_player = new SwitchPlayer(next_player, loop, false);

    scroll_area_hand->hide();
    mid_column->addWidget(change_player);
    change_player->setMinimumHeight(scroll_area_hand->sizeHint().height());

    loop.exec();

    mid_column->removeWidget(change_player);
    delete change_player;
    scroll_area_hand->show();
}

//Set up the layout of all the elements in the gui
void Gui::uiElements()
{
    //Init game ui widgets
    log_widget = new LogWidget(player_ids, this);
    player_list_widget = new PlayerList(player_ids, this);
    deck_widget = new DeckButton(this);
    trash_widget = new TrashButton(this);
    goals_widget = new GoalButtons(this);
    rules_widget = new RulesGridWidget(this);
    active_hand = new ActiveHand(this);
    active_keepers = new ActiveKeepers(this);

    //Init window layout elements
    //A lot of these could probably be replaces with a single grid layout instead.
    layout = new QHBoxLayout();
    mid_column = new QVBoxLayout();
    mid_column_right = new QVBoxLayout();
    left_column = new QVBoxLayout();
    rules_goals_row = new QHBoxLayout();
    rules_keepers_column = new QVBoxLayout();

    //Remove spacing from layout
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0); // Remove margins for window borders
    mid_column->setSpacing(0);
    mid_column_right->setSpacing(0);
    left_column->setSpacing(0);
    rules_goals_row->setSpacing(0);
    rules_keepers_column->setSpacing(0);

    //Set up properties of the game window, background, titlebar etc.
    this->setAutoFillBackground(true);
    this->setPalette(Qt::white);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    this->setWindowTitle(QString("Fluxx"));
    this->setMinimumSize(640, 480);

    this->setLayout(layout);

    //Init scroll areas
    scroll_area_rules = new QScrollArea();
    scroll_area_hand = new QScrollArea();
    scroll_area_keepers = new QScrollArea();

    //Assign widgets to scroll areas
    scroll_area_keepers->setWidget(active_keepers);
    scroll_area_hand->setWidget(active_hand);
    scroll_area_rules->setWidget(rules_widget);

    //Remove border from scroll areas
    scroll_area_rules->setFrameStyle(QFrame::NoFrame);
    scroll_area_keepers->setFrameShape(QFrame::NoFrame);
    scroll_area_hand->setFrameShape(QFrame::NoFrame);

    //Set scroll areas to only horizontal scrolling
    scroll_area_hand->setMinimumHeight(active_hand->minimumSizeHint().height() + scroll_area_hand->horizontalScrollBar()->height() + 20);
    scroll_area_hand->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area_keepers->setMinimumWidth(active_keepers->minimumSizeHint().width() + 25);
    scroll_area_keepers->setMinimumHeight(active_keepers->minimumSizeHint().height() + scroll_area_keepers->horizontalScrollBar()->height() + 5);
    scroll_area_keepers->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Add widgets to layouts
    left_column->addWidget(trash_widget);
    left_column->addWidget(log_widget);
    mid_column_right->addWidget(deck_widget);
    mid_column_right->addWidget(goals_widget);
    rules_keepers_column->addWidget(scroll_area_rules);
    rules_keepers_column->addWidget(scroll_area_keepers);

    rules_goals_row->addLayout(rules_keepers_column);
    rules_goals_row->addLayout(mid_column_right);

    mid_column->addLayout(rules_goals_row);
    mid_column->addWidget(scroll_area_hand);

    layout->addLayout(left_column);
    layout->addLayout(mid_column);
    layout->addWidget(player_list_widget);

    //Set alignments
    mid_column_right->setAlignment(deck_widget, Qt::AlignRight | Qt::AlignTop);
    mid_column_right->setAlignment(goals_widget, Qt::AlignTrailing);
    rules_goals_row->setAlignment(rules_keepers_column, Qt::AlignTop);
    rules_goals_row->setAlignment(mid_column_right, Qt::AlignRight|Qt::AlignTop);
    mid_column->setAlignment(scroll_area_hand, Qt::AlignBottom);
    this->showMaximized();
}
