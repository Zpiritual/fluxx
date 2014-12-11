#include "newgame.h"


NewGame::NewGame(const std::vector<Profile>& profiles, const Deck* const dck, QWidget *parent) :
    QWidget(parent)
{
    uiElementSetup();
    deck = dck;
    parent2 = dynamic_cast<MainMenu*>(parent);

    addToPlayerList(profiles);
}

NewGame::~NewGame()
{
    delete player_list;
    delete select_player_button;
    delete start_button;
    delete back_button;
    delete view_players;
    delete finish_layout;
    delete list_layout;
    delete others_layout;
    delete layout;
}

void NewGame::message(const QString& title, const QString& message) const
{
    // Display a message box
    QMessageBox message_dialog;
    message_dialog.setWindowTitle(title);
    message_dialog.setText(message);
    message_dialog.exec();
}

bool NewGame::existPlayer(const ProfileName& player_id) const
{
    for(unsigned int i = 0; i < players.size(); i++)
    {
        if(players.at(i) == player_id)
        {
            return true;
        }
    }
    return false;
}

void NewGame::addToPlayerList(const std::vector<Profile>& profiles)
{
    for(unsigned i = 0; i < profiles.size(); i++)
    {
        player_list->addItem(QString::fromStdString(profiles.at(i).getName()));
    }
}

void NewGame::addPlayer(QListWidgetItem* player)
{
    if(existPlayer(ProfileName(player->text().toStdString())))
    {
        message(QString("New Game"), player->text() + QString(" is already chosen."));
    }
    else
    {
        QString temp = view_players->text();
        temp = temp + "\nPlayer " + QString::number(current_player++) + ": " + player->text();
        view_players->setText(temp);
        players.push_back(ProfileName{player->text().toStdString()});
    }
}

void NewGame::startGame()
{
    if(current_player < 3)
    {
        message(QString{"New Game"}, QString{"Atleast 2 players needed to start game."});
    }
    else
    {
        Gui* gui = new Gui(players, parent2);

        gui->move(QApplication::desktop()->screen()->rect().center() - gui->rect().center());

        GameLoop game_loop(GameLoop(gui, deck, players.size()));

        gui->show();

        parent2->hide();

        SessionData session_data = game_loop.run();

        qDebug() << "GameLoop Exited successfully";
        if(session_data.game_state == GameState::GAME_OVER)
        {
            parent2->gameOverScreen(session_data, players);
        }
        else
        {
            parent2->newGameBack();
        }
        parent2->show();
        delete gui;
    }
}

void NewGame::selectPlayer()
{
    const QListWidgetItem* selected = player_list->currentItem();
    if(existPlayer(ProfileName(selected->text().toStdString())))
    {
        message(QString("New Game"), selected->text() + QString(" is already chosen."));
    }
    else if(current_player <= 6)
    {
        QString temp = view_players->text();
        temp = temp + "\nPlayer " + QString::number(current_player++) + ": " + selected->text();
        view_players->setText(temp);
        players.push_back(ProfileName{selected->text().toStdString()});
    }
    else
    {
        message(QString("New Game"), QString("6 players are the limit."));
    }
    player_list->clearSelection();
    select_player_button->setEnabled(false);
}

void NewGame::selectPlayers()
{
    QList<QListWidgetItem*> selected_items = player_list->selectedItems();
    if(selected_items.size() > 6)
    {
        for(int i = 0; i < 6; i++)
        {
            addPlayer(selected_items.at(i));
        }
    }
    else
    {
        for(int i = 0; i < selected_items.size(); i++)
        {
            addPlayer(selected_items.at(i));
        }
    }
}

void NewGame::enableSelectPlayerButton()
{
    if(player_list->selectedItems().size() != 0)
        select_player_button->setEnabled(true);
    else
        select_player_button->setEnabled(false);
}

void NewGame::uiElementSetup()
{
    layout = new QHBoxLayout();
    list_layout = new QVBoxLayout();
    others_layout = new QVBoxLayout();
    finish_layout = new QHBoxLayout();

    player_list = new QListWidget();
    view_players = new QLabel();

    select_player_button = new QPushButton(QString("Select players"));
    start_button = new QPushButton(QString("Start Game"));
    back_button = new QPushButton(QString("Cancel"));

    select_player_button->setEnabled(false);

    player_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

    list_layout->addWidget(player_list);
    list_layout->addWidget(select_player_button);

    others_layout->addWidget(view_players);
    others_layout->setAlignment(view_players, Qt::AlignTop);

    finish_layout->addWidget(start_button);
    finish_layout->addWidget(back_button);

    others_layout->addLayout(finish_layout);
    others_layout->setAlignment(finish_layout, Qt::AlignBottom);

    connectSignals();

    layout->addLayout(list_layout);
    layout->addLayout(others_layout);

    this->setLayout(layout);
}

void NewGame::connectSignals()
{
    QObject::connect(start_button, SIGNAL(clicked()), this, SLOT(startGame()));
    QObject::connect(select_player_button, SIGNAL(clicked()), this, SLOT(selectPlayers()));
    QObject::connect(back_button, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject::connect(player_list, SIGNAL(itemSelectionChanged()), this, SLOT(enableSelectPlayerButton()));
    QObject::connect(player_list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(selectPlayer()));
}

void NewGame::goBack()
{
    if(parent2 != nullptr)
    {
        parent2->newGameBack();
    }
    else
    {
        message(QString("Error"), QString("parent2 does not exist"));
    }
}
