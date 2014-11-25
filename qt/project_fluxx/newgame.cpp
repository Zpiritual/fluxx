#include "newgame.h"
#include "mainmenu.h"
#include "gui.h"
#include "PlayerID.h"
#include <sstream>
#include "Player.h"

NewGame::NewGame(const std::vector<Profile>& profiles, QWidget *parent) :
    QWidget(parent)
{
    uiElementSetup();
    parent2 = dynamic_cast<MainMenu*>(parent);

    for(unsigned i = 0; i < profiles.size(); i++)
    {
        player_list->addItem(QString::fromStdString(profiles.at(i).getName()));
    }
}

NewGame::~NewGame()
{
}

void NewGame::message(const QString& title, const QString& message) const
{
    // Display a message box
    QMessageBox message_dialog;
    message_dialog.setWindowTitle(title);
    message_dialog.setText(message);
    message_dialog.exec();
}

bool NewGame::existPlayer(const QString& name) const
{
    std::istringstream ss;
    ss.str(view_players->text().toStdString());
    std::string temp;
    while(ss >> temp)
    {
        if(temp == name.toStdString())
        {
            return true;
        }
    }
    return false;
}

void NewGame::startGame()
{
    std::vector<PlayerID> pvector{std::string{"Rasmus"}, std::string{"Fredrik"}, std::string{"Martin"}};

    Gui* gui = new Gui(pvector);

    gui->move(QApplication::desktop()->screen()->rect().center() - gui->rect().center());



    //TESTFUNKTION NEDAN
    CardContainer deckcontainer = CardContainer(CardContainerID("Deck"));
    CardContainer trashcontainer = CardContainer(CardContainerID("Trash"));
    CardContainer rulescontainer = CardContainer(CardContainerID("Rules"));
    CardContainer player1container_hand = CardContainer(CardContainerID("Player1_hand"));
    CardContainer player2container_hand = CardContainer(CardContainerID("Player2_hand"));
    CardContainer goalscontainer = CardContainer(CardContainerID("Goals"));
    CardContainer player1container_keepers = CardContainer(CardContainerID("Player1_keepers"));
    CardContainer player2container_keepers = CardContainer(CardContainerID("Player2_keepers"));



    for(unsigned i = 1; i <= 82; ++i)
    {
       if(i > 3 && i< 10)
       {
            player1container_hand.addCard(CardID(i));
            qDebug() << "add hand1" << i;
       }

        else if(i > 9 && i < 13)
       {
            player2container_hand.addCard(CardID(i));
            qDebug() << "add hand2" << i;
       }
        else if(i == 22)
       {
            goalscontainer.addCard(CardID(i));
            qDebug() << "add hand2" << i;
       }
        else if(i > 66 && i < 69)
            player1container_keepers.addCard(CardID(i));
        else if(i == 79 || i ==80)
            player2container_keepers.addCard(CardID(i));
        else if(i >= 50 && i <= 55)
            rulescontainer.addCard(CardID(i));
        else if(i >= 13 && i < 22)
            trashcontainer.addCard(CardID(i));
        else
            deckcontainer.addCard(CardID(i));
    }


    std::vector<CardContainer>* bcontainer = new std::vector<CardContainer>;
    bcontainer->push_back(deckcontainer);
    bcontainer->push_back(trashcontainer);
    bcontainer->push_back(rulescontainer);
    bcontainer->push_back(player1container_hand);
    bcontainer->push_back(player1container_keepers);
    bcontainer->push_back(player2container_hand);
    bcontainer->push_back(player2container_keepers);
    bcontainer->push_back(goalscontainer);

    gui->update(bcontainer);

    gui->show();

    gui->pickCard(CardContainerID("Rules"));

    qDebug() << "Add startGame functionality";
}

void NewGame::goBack(){
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

void NewGame::selectPlayer()
{
    const QListWidgetItem* selected = player_list->currentItem();
    if(existPlayer(selected->text()))
    {
        message(QString("New Game"), QString("Player is already chosen."));
    }
    else if(current_player <= 6)
    {
        QString temp = view_players->text();
        temp = temp + "\nPlayer " + QString::number(current_player++) + ": " + selected->text();
        view_players->setText(temp);
    }
    else
    {
        message(QString("New Game"), QString("6 players are the limit."));
    }
    player_list->clearSelection();
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

    QObject::connect(start_button, SIGNAL(clicked()), this, SLOT(startGame()));
    QObject::connect(select_player_button, SIGNAL(clicked()), this, SLOT(selectPlayer()));
    QObject::connect(back_button, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject::connect(player_list, SIGNAL(clicked(QModelIndex)), this, SLOT(enableSelectPlayerButton()));

    layout->addLayout(list_layout);
    layout->addLayout(others_layout);

    this->setLayout(layout);
}

