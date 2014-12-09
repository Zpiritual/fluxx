#include "newgame.h"


NewGame::NewGame(const std::vector<Profile>& profiles, const Deck* const dck, QWidget *parent) :
    QWidget(parent)
{
    uiElementSetup();
    deck = dck;
    parent2 = dynamic_cast<MainMenu*>(parent);

    for(unsigned i = 0; i < profiles.size(); i++)
    {
        player_list->addItem(QString::fromStdString(profiles.at(i).getName()));
    }
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

        qDebug() << "Add startGame functionality";
        parent2->gameOverScreen(session_data, players);
        parent2->show();
        delete gui;
    }
}

void NewGame::selectPlayer()
{
    const QListWidgetItem* selected = player_list->currentItem();
    if(existPlayer(ProfileName(selected->text().toStdString())))
    {
        message(QString("New Game"), QString("Player is already chosen."));
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
    qDebug() << "Add selectPlayer functionality";
}

void NewGame::enableSelectPlayerButton()
{
    select_player_button->setEnabled(true);
}

void NewGame::uiElementSetup()
{
    layout = new QHBoxLayout();
    list_layout = new QVBoxLayout();
    others_layout = new QVBoxLayout();
    finish_layout = new QHBoxLayout();

    player_list = new QListWidget();
    view_players = new QLabel();

    select_player_button = new QPushButton(QString("Select player"));
    start_button = new QPushButton(QString("Start Game"));
    back_button = new QPushButton(QString("Cancel"));

    select_player_button->setEnabled(false);

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
    QObject::connect(select_player_button, SIGNAL(clicked()), this, SLOT(selectPlayer()));
    QObject::connect(back_button, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject::connect(player_list, SIGNAL(clicked(QModelIndex)), this, SLOT(enableSelectPlayerButton()));
    QObject::connect(player_list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(selectPlayer()));
}

void NewGame::goBack()
{
    qDebug() << "Add goBack functionality";

    if(parent2 != nullptr)
    {
        parent2->newGameBack();
    }
    else
    {
        message(QString("Error"), QString("parent2 does not exist"));
    }
}
