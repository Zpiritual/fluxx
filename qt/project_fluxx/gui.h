#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QtWidgets>
#include <logwidget.h>
#include <playerlist.h>
#include <rulesgridwidget.h>
#include <activeplayer.h>

class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

private:
    QHBoxLayout* layout;
    LogWidget* log_widget;
    PlayerList* player_list_widget;
    RulesGridWidget* rules_widget;
    ActivePlayer* active_player_widget;
    QVBoxLayout* mid_column;

    signals:

public slots:

};

#endif // GUI_H
