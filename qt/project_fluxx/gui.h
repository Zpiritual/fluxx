#ifndef GUI_H
#define GUI_H


#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "logwidget.h"
#include "playerlist.h"
#include "rulesgridwidget.h"
#include "activeplayer.h"
#include "../../include/BoardSnapshot.h"
#include "../../include/CardID.h"
#include "../../include/ContainerID.h"
#include "../../include/PlayerID.h"

class Gui : public QWidget
{
    Q_OBJECT
public:  
    explicit Gui(std::vector<PlayerID> players, QWidget *parent = 0);
    ~Gui();
    const PlayerID pickPlayer(const BoardSnapshot);
    const CardID pickCard(BoardSnapshot, ContainerID);
    void update(const BoardSnapshot);
    void nextPlayer();



private:
    QHBoxLayout* layout;
    LogWidget* log_widget;
    PlayerList* player_list_widget;
    RulesGridWidget* rules_widget;
    ActivePlayer* active_player_widget;
    QVBoxLayout* mid_column;
    std::vector<PlayerID> player_ids;

    signals:

public slots:

};

#endif // GUI_H
