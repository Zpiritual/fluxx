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
    const PlayerID pickPlayer(const BoardSnapshot * const);
    const CardID pickCard(const BoardSnapshot* const, const CardContainerID);
    const CardID pickCard(const BoardSnapshot* const, const CardContainerID, const PlayerID);
    void nextPlayer(const BoardSnapshot* const);
    const Direction chooseDirection(const BoardSnapshot * const snapshot);

    void closeEvent(QCloseEvent*);

private:
    void update(const BoardSnapshot* const);
    QHBoxLayout* layout;
    LogWidget* log_widget;
    PlayerList* player_list_widget;
    RulesGridWidget* rules_widget;
    ActivePlayer* active_player_widget;
    QVBoxLayout* mid_column;
    QHBoxLayout* mid_column_top;
    std::vector<ProfileName> player_ids;
    DeckButton* deck_widget;
    GoalButtons* goals_widget;
    TrashButton* trash_widget;
    QVBoxLayout* left_column;

    void message(const QString&, const QString&) const;


    signals:

public slots:


};

#endif // GUI_H
