//Class used when the players switch turns and is used to in replacement to active hand.

#ifndef SWITCHPLAYER_H
#define SWITCHPLAYER_H

#include <QWidget>
#include "profilename.h"
#include <QtWidgets>

class SwitchPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchPlayer(const ProfileName&, QEventLoop&, const bool, QWidget *parent = 0);
    ~SwitchPlayer();
    void uiElements(const ProfileName&, const bool);
    void connectSignals(QEventLoop& loop);

private:
    QHBoxLayout* main_layout;
    QVBoxLayout* next_player_layout;
    QPushButton* next_player_button;
    QLabel* next_player_text;
};

#endif // SWITCHPLAYER_H
