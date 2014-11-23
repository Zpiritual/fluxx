#ifndef SWITCHPLAYER_H
#define SWITCHPLAYER_H

#include <QWidget>
#include <QtWidgets>

class SwitchPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchPlayer(QWidget *parent = 0);
    void uiElements();
    void connectSignals();

private:
    QHBoxLayout* main_layout;
    QVBoxLayout* next_player_layout;
    QVBoxLayout* new_player_layout;

    QPushButton* next_player_button;
    QPushButton* new_player_button;

    QLineEdit* name_field;
    QLabel* next_player_text;


signals:

public slots:
    void enableNewPlayerButton();
    void nextPlayer();
    void newPlayer();

};

#endif // SWITCHPLAYER_H
