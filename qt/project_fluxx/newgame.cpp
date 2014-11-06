#include "newgame.h"

NewGame::NewGame(QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout();
    player_list = new QListWidget();
    text_field = new QLineEdit();
    select_player_button = new QPushButton();
    start_button = new QPushButton();
    back_button = new QPushButton();
}

NewGame::~NewGame()
{
}

void startGame()
{
    qDebug() << "Add startGame functionality";


}

void nextPlayer(){
    qDebug() << "Add nexPlayer functionality";
}

void goBack(){
    qDebug() << "Add goBack functionality";
}

void selectPlayer()
{
    qDebug() << "Add selectPlayer functionality";
}

