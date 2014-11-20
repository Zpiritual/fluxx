#ifndef GOALBUTTONS_H
#define GOALBUTTONS_H

#include <QWidget>
#include <QtWidgets>
#include "../../include/CardID.h"

class GoalButtons : public QWidget
{
    Q_OBJECT
public:
    explicit GoalButtons(QWidget *parent = 0);
    void updateCards(const std::vector<CardID>&);
    ~GoalButtons();

private:
    std::vector<CardID> cards;
    QHBoxLayout* layout;


signals:

public slots:

};

#endif // GOALBUTTONS_H
