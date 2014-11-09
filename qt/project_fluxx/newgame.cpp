#include "newgame.h"
#include "mainmenu.h"

NewGame::NewGame(QWidget *parent) :
    QWidget(parent)
{
    uiElementSetup();
    parent2 = dynamic_cast<MainMenu*>(parent);
    player_list->addItem(QString("Player1"));
    player_list->addItem(QString("Player2"));
    player_list->addItem(QString("Player3"));
}

NewGame::~NewGame()
{
}

void NewGame::startGame()
{
    qDebug() << "Add startGame functionality";
}

void NewGame::nextPlayer(){
    qDebug() << "Add nexPlayer functionality";

    if(current_player <= 6)
    {
        QString temp = view_players->text();
        temp = temp + "\nPlayer " + QString::number(current_player++) + ": " + text_field->text();
        view_players->setText(temp);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Only 6 players are allowed to play");
        msgBox.setWindowTitle("ERROR!");
        msgBox.exec();
    }
}

void NewGame::goBack(){
      qDebug() << "Add goBack functionality";
      parent2->newGameBack();
    //parent2->changeLayout(this, parent2->getStart());
    //qDebug() << "Int:" << parent()->testing;

}

void NewGame::selectPlayer()
{
    const QListWidgetItem* selected = player_list->currentItem();
    text_field->setText(selected->text());

    qDebug() << "Add selectPlayer functionality";
}

void NewGame::uiElementSetup()
{
    layout = new QHBoxLayout();
    list_layout = new QVBoxLayout();
    others_layout = new QVBoxLayout();
    finish_layout = new QHBoxLayout();

    player_list = new QListWidget();
    text_field = new QLineEdit();
    view_players = new QLabel();

    select_player_button = new QPushButton(QString("Select player"));
    next_player_button = new QPushButton(QString("Next Player"));
    start_button = new QPushButton(QString("Start Game"));
    back_button = new QPushButton(QString("Cancel"));

    list_layout->addWidget(player_list);
    list_layout->addWidget(select_player_button);

    others_layout->addWidget(text_field);
    others_layout->addWidget(next_player_button);
    others_layout->addWidget(view_players);
    others_layout->setAlignment(view_players, Qt::AlignTop);


    finish_layout->addWidget(start_button);
    finish_layout->addWidget(back_button);

    others_layout->addLayout(finish_layout);
    others_layout->setAlignment(finish_layout, Qt::AlignBottom);

    QObject::connect(start_button, SIGNAL(clicked()), this, SLOT(startGame()));
    QObject::connect(select_player_button, SIGNAL(clicked()), this, SLOT(selectPlayer()));
    QObject::connect(next_player_button, SIGNAL(clicked()), this, SLOT(nextPlayer()));
    QObject::connect(back_button, SIGNAL(clicked()), this, SLOT(goBack()));


    layout->addLayout(list_layout);
    layout->addLayout(others_layout);

    this->setLayout(layout);
}

