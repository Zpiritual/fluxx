#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include "QtWidgets"
#include "SessionData.h"
#include "mainmenu.h"
#include "profilename.h"
#include "PlayerStats.h"
class GameOver : public QWidget
{
    Q_OBJECT
public:
    explicit GameOver(SessionData, std::vector<ProfileName>, QWidget *parent = 0);

private:
    QVBoxLayout* layout;
    QPushButton* ok_button;
    QLabel* winning_player_label;
    QLabel* time_played_label;
    QLabel* stats_label;
    void uiElementSetup(SessionData session_data, std::vector<ProfileName>);
    void connectSignals();
    ProfileName winning_player_name;
    MainMenu* parent2;


signals:

public slots:
    void returnToMainMenu();

};

#endif // GAMEOVER_H
