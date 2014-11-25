#ifndef GOALBUTTONS_H
#define GOALBUTTONS_H

#include <QWidget>
#include <QtWidgets>
#include "CardID.h"
#include "CardContainer.h"
class CardButton;

class GoalButtons : public QWidget
{
    Q_OBJECT
public:
    explicit GoalButtons(QWidget *parent = 0);
    void updateCards(const CardContainer&);
    ~GoalButtons();

private:
    std::vector<CardID> cards_;
    QHBoxLayout* layout;


signals:

public slots:
};
#include "cardbutton.h"

#endif // GOALBUTTONS_H
