#ifndef SWITCHPLAYER_H
#define SWITCHPLAYER_H

#include <QWidget>
#include "profilename.h"
#include <QtWidgets>

class SwitchPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchPlayer(const ProfileName&, QEventLoop&, QWidget *parent = 0);
    void uiElements(const ProfileName&);
    void connectSignals(QEventLoop& loop);

private:
    QHBoxLayout* main_layout;
    QVBoxLayout* next_player_layout;

    QPushButton* next_player_button;

    QLabel* next_player_text;


signals:

public slots:
    void nextPlayer();

};

#endif // SWITCHPLAYER_H
