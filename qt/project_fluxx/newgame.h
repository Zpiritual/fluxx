//Class shown in the main menu that is used for starting the game.

#ifndef NEWGAME_H
#define NEWGAME_H

#include <QWidget>
#include <QtWidgets>
#include "mainmenu.h"
#include "gui.h"
#include "profilename.h"
#include "GameLoop.h"
#include "SessionData.h"

class NewGame : public QWidget
{
    Q_OBJECT
public:
    explicit NewGame(const std::vector<Profile>&, const Deck* const, QWidget *parent = 0);
    ~NewGame();


private:
    QHBoxLayout* layout;
    QVBoxLayout* list_layout;
    QVBoxLayout* others_layout;
    QHBoxLayout* finish_layout;
    QListWidget* player_list;
    QPushButton* select_player_button;
    QPushButton* start_button;
    QPushButton* back_button;
    QLabel* view_players;
    int current_player = 1;
    MainMenu* parent2;

    const Deck* deck;

    std::vector<ProfileName> players;

    void uiElementSetup();
    void connectSignals();
    void message(const QString&, const QString&) const;
    bool existPlayer(const ProfileName&) const;
    void addToPlayerList(const std::vector<Profile>&);
    void addPlayer(QListWidgetItem*);

signals:

public slots:
    void startGame();
    void goBack();
    void selectPlayer();
    void selectPlayers();
    void enableSelectPlayerButton();
};

#endif // NEWGAME_H
