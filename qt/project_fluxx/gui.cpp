#include "gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();
    log_widget = new LogWidget(this);
    player_list_widget = new PlayerList(this);
    rules_widget = new RulesGridWidget(this);
    active_player_widget = new ActivePlayer(this);
    mid_column = new QVBoxLayout();

    mid_column->addWidget(rules_widget);
    mid_column->addWidget(active_player_widget);

    mid_column->setAlignment(active_player_widget, Qt::AlignBottom);
    //mid_column->setAlignment()

    this->setMinimumHeight(1024);
    this->setMinimumWidth(1280);
    this->setWindowTitle(QString("Fluxx"));

    layout->addWidget(log_widget);
    layout->addLayout(mid_column);
    layout->addWidget(player_list_widget);

    layout->setAlignment(log_widget, Qt::AlignLeft);



    this->setLayout(layout);
}

Gui::~Gui(){
}
