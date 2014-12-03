#ifndef GOALBUTTONS_H
#define GOALBUTTONS_H

#include <QWidget>
#include <QtWidgets>
#include "CardID.h"
#include "CardContainer.h"
#include "cardbutton.h"
#include "cardidloop.h"
#include "bigcardcollection.h"

class GoalButtons : public QWidget
{
    Q_OBJECT
public:
    explicit GoalButtons(QWidget *parent = 0);
    void updateCards(const CardContainer&);
    void setConnections(CardIdLoop& loop);
    ~GoalButtons();

private:
    std::vector<CardButton*> buttons_;
    QHBoxLayout* layout;
    std::vector<CardID> cards_;

    void uiElements();

signals:

public slots:
};

#endif // GOALBUTTONS_H
