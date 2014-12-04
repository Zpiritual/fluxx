#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "logwidget.h"
#include "rulesgridwidget.h"
#include "deckbutton.h"
#include "goalbuttons.h"
#include "trashbutton.h"
#include "BoardSnapshot.h"
#include "CardID.h"
#include "switchplayer.h"
#include "CardContainerID.h"
#include "PlayerID.h"
#include "playerlist.h"
#include "activeplayer.h"
#include "profilename.h"
#include "cardidloop.h"
#include "playerloop.h"


class Gui : public QWidget
{
    Q_OBJECT
public:  
    explicit Gui(std::vector<ProfileName> players, QWidget *parent = 0);
    ~Gui();
    PlayerID pickPlayer(const BoardSnapshot * const);
    CardID pickCard(const BoardSnapshot* const, const CardContainerID);
    CardID pickCard(const BoardSnapshot* const);
    void nextPlayer(const BoardSnapshot* const);
    Direction chooseDirection(const BoardSnapshot * const);
    bool playerDecision(const BoardSnapshot* const, const std::string&, const std::string&, const std::string&);


    void closeEvent(QCloseEvent*);

private:
    void update(const BoardSnapshot* const, const bool);
    QHBoxLayout* layout;
    LogWidget* log_widget;
    PlayerList* player_list_widget;
    RulesGridWidget* rules_widget;
    ActivePlayer* active_player_widget;
    QVBoxLayout* mid_column;
    QVBoxLayout* mid_column_right;
    QHBoxLayout* rules_goals_row;
    std::vector<ProfileName> player_ids;
    DeckButton* deck_widget;
    GoalButtons* goals_widget;
    TrashButton* trash_widget;
    QVBoxLayout* left_column;
    CardIdLoop* card_id_loop;
    PlayerLoop* player_loop;
    QEventLoop* event_loop;
    QScrollArea* rules_scroll;

    void message(const QString&, const QString&) const;
    void uiElements();


    signals:

public slots:


};

#endif // GUI_H
