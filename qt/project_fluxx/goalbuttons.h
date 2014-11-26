#ifndef GOALBUTTONS_H
#define GOALBUTTONS_H

#include <QWidget>
#include <QtWidgets>
#include "CardID.h"
#include "CardContainer.h"
#include "cardbutton.h"

class GoalButtons : public QWidget
{
    Q_OBJECT
public:
    explicit GoalButtons(QWidget *parent = 0);
    void update(const CardContainer&);
    void setConnections(QEventLoop& loop);
    ~GoalButtons();

private:
    std::vector<CardButton*> buttons_;
    QHBoxLayout* layout;


signals:

public slots:
};

#endif // GOALBUTTONS_H
