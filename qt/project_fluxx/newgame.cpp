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
//    std::vector<CardContainer>* bcontainer = new std::vector<CardContainer>;
//    bcontainer->push_back(deckcontainer);
//    bcontainer->push_back(trashcontainer);
//    bcontainer->push_back(rulescontainer);
//    bcontainer->push_back(player1container_hand);
//    bcontainer->push_back(player1container_keepers);
//    bcontainer->push_back(player2container_hand);
//    bcontainer->push_back(player2container_keepers);
//    bcontainer->push_back(goalscontainer);
//    bcontainer->push_back(CardContainer(CardContainerID("tempA")));
//    bcontainer->push_back(CardContainer(CardContainerID("tempB")));

//    BoardSnapshot* snapshot = new BoardSnapshot(*bcontainer,2,PlayerID(PlayerIdentifier::Player1),2,1, Direction::CLOCKWISE);

  //  GameLoop* game_loop = new GameLoop(gui);

 //   gui->show();
//    game_loop->run();

//    CardID temp = gui->pickCard(snapshot, CardContainerID("Rules"));
//    qDebug() << "You picked card " + QString::number(temp.val);

//    temp = gui->pickCard(snapshot, CardContainerID("Trash"));
//    qDebug() << "You picked card " + QString::number(temp.val);

//   CardContainer deckcontainer2 = CardContainer(CardContainerID("Deck"));
//   CardContainer trashcontainer2 = CardContainer(CardContainerID("Trash"));
//   CardContainer rulescontainer2 = CardContainer(CardContainerID("Rules"));
//   CardContainer player1container_hand2 = CardContainer(CardContainerID("Player1_hand"));
//   CardContainer player2container_hand2 = CardContainer(CardContainerID("Player2_hand"));
//   CardContainer goalscontainer2 = CardContainer(CardContainerID("Goals"));
//   CardContainer player1container_keepers2 = CardContainer(CardContainerID("Player1_keepers"));
//   CardContainer player2container_keepers2 = CardContainer(CardContainerID("Player2_keepers"));



//   for(unsigned i = 1; i <= 82; ++i)
//   {
//      if(i > 10 && i< 13)
//      {
//           player1container_hand2.addCard(CardID(i));
//           qDebug() << "add hand1" << i;
//      }

//       else if(i > 22 && i < 28)
//      {
//           player2container_hand2.addCard(CardID(i));
//           qDebug() << "add hand2" << i;
//      }
//       else if(i == 45)
//      {
//           goalscontainer2.addCard(CardID(i));
//           qDebug() << "add hand3" << i;
//      }
//       else if(i > 70 && i < 76)
//           player1container_keepers2.addCard(CardID(i));
//       else if(i == 46 || i ==29)
//           player2container_keepers2.addCard(CardID(i));
//       else if(i >= 15 && i <= 22)
//           rulescontainer2.addCard(CardID(i));
//       else if(i >= 76 && i < 79)
//           trashcontainer2.addCard(CardID(i));
//       else
//           deckcontainer2.addCard(CardID(i));
//   }

//   std::vector<CardContainer>* bcontainer2 = new std::vector<CardContainer>;
//   bcontainer2->push_back(deckcontainer2);
//   bcontainer2->push_back(trashcontainer2);
//   bcontainer2->push_back(rulescontainer2);
//   bcontainer2->push_back(player1container_hand2);
//   bcontainer2->push_back(player1container_keepers2);
//   bcontainer2->push_back(player2container_hand2);
//   bcontainer2->push_back(player2container_keepers2);
//   bcontainer2->push_back(goalscontainer2);
//   bcontainer2->push_back(CardContainer(CardContainerID("tempA")));
//   bcontainer2->push_back(CardContainer(CardContainerID("tempB")));

//   BoardSnapshot* snapshot2 = new BoardSnapshot(*bcontainer2,2,PlayerID(PlayerIdentifier::Player1),2,1, Direction::CLOCKWISE);
//    qDebug() << "You're going to switch player";
//    gui->nextPlayer(snapshot2);

//    PlayerID player_id = gui->pickPlayer(snapshot2);
//    qDebug() << QString("Player ID: ") << QString::fromStdString(player_id.getString());
//>>>>>>> f696229da1a4135d5b1354a285dcda892cc60d6b
