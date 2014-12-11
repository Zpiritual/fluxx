//Contains the main class for the actual game itself. Also contain the interface used by the gameloop.

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
#include "profilename.h"
#include "cardidloop.h"
#include "playerloop.h"
#include "mainmenu.h"
#include "activehand.h"
#include "activekeepers.h"


class Gui : public QWidget
{
    Q_OBJECT
public:  
    explicit Gui(std::vector<ProfileName> players, MainMenu* main_menu, QWidget *parent = 0);
    ~Gui();
    PlayerID pickPlayer(const BoardSnapshot * const);
    CardID pickCard(const BoardSnapshot* const, const CardContainerID);
    CardID pickCard(const BoardSnapshot* const);
    void nextPlayer(const BoardSnapshot* const);
    bool playerDecision(const BoardSnapshot* const, const std::string&, const std::string&, const std::string&);


    void closeEvent(QCloseEvent*);

private:
    QHBoxLayout* layout;
    LogWidget* log_widget;
    PlayerList* player_list_widget;
    RulesGridWidget* rules_widget;
    QVBoxLayout* mid_column;
    QVBoxLayout* mid_column_right;
    QHBoxLayout* rules_goals_row;
    QVBoxLayout* rules_keepers_column;
    std::vector<ProfileName> player_ids;
    DeckButton* deck_widget;
    GoalButtons* goals_widget;
    TrashButton* trash_widget;
    QVBoxLayout* left_column;
    CardIdLoop* card_id_loop;
    PlayerLoop* player_loop;
    QEventLoop* event_loop;
    QScrollArea* scroll_area_rules;
    MainMenu* _parent;
    PlayerID previous_active_player;
    QScrollArea* scroll_area_hand;
    QScrollArea* scroll_area_keepers;
    ActiveHand* active_hand;
    ActiveKeepers* active_keepers;

    void update(const BoardSnapshot* const, const bool);
    void uiElements();
    void changePlayer(const ProfileName &next_player, QEventLoop &loop);
    void endTurn(const ProfileName&, QEventLoop&);
    void connectActiveKeepers(CardIdLoop&);
    void connectActiveHand(CardIdLoop&);
    void updateActiveHandAndKeepers(const BoardSnapshot* const, const bool);
};

#endif // GUI_H
