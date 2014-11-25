#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "logwidget.h"
#include "rulesgridwidget.h"
#include "deckbutton.h"
//#include "activeplayer.h"
#include "goalbuttons.h"
#include "trashbutton.h"
#include "BoardSnapshot.h"
#include "CardID.h"
#include "CardContainerID.h"
#include "PlayerID.h"

class ActivePlayer;
class PlayerList;

class Gui : public QWidget
{
    Q_OBJECT
public:  
    explicit Gui(std::vector<PlayerID> players, QWidget *parent = 0);
    ~Gui();
    const PlayerID pickPlayer(BoardSnapshot*);
    const CardID pickCard(const CardContainerID&);
    void update(BoardSnapshot*);
    void update(std::vector<CardContainer>*);
    void nextPlayer();

private:
    QHBoxLayout* layout;
    LogWidget* log_widget;
    PlayerList* player_list_widget;
    RulesGridWidget* rules_widget;
    ActivePlayer* active_player_widget;
    QVBoxLayout* mid_column;
    QHBoxLayout* mid_column_top;
    std::vector<PlayerID> player_ids;
    DeckButton* deck_widget;
    GoalButtons* goals_widget;
    TrashButton* trash_widget;

    signals:

public slots:


};

#include "playerlist.h"
#include "activeplayer.h"
#endif // GUI_H
