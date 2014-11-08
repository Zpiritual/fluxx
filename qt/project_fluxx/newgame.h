#ifndef NEWGAME_H
#define NEWGAME_H

#include <QWidget>
#include <QtWidgets>

class NewGame : public QWidget
{
    Q_OBJECT
public:
    explicit NewGame(QWidget *parent = 0);
    ~NewGame();

private:
    QHBoxLayout* layout;
    QVBoxLayout* list_layout;
    QVBoxLayout* others_layout;
    QHBoxLayout* finish_layout;
    QListWidget* player_list;
    QPushButton* select_player_button;
    QLineEdit* text_field;
    QPushButton* next_player_button;
    QPushButton* start_button;
    QPushButton* back_button;
    QLabel* view_players;
    int current_player = 1;

    void uiElementSetup();


signals:

public slots:
    void startGame();
    void nextPlayer();
    void goBack();
    void selectPlayer();
};

#endif // NEWGAME_H
