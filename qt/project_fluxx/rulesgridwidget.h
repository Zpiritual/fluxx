#ifndef RULESGRIDWIDGET_H
#define RULESGRIDWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "CardContainer.h"
#include "cardbutton.h"
#include "cardidloop.h"

class RulesGridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RulesGridWidget(QWidget *parent = 0);
    ~RulesGridWidget();
    void updateCards(const CardContainer);
    void setConnections(CardIdLoop&);

private:
    QGridLayout* layout;
    std::vector<CardButton*> buttons_;

signals:

public slots:

};



#endif // RULESGRIDWIDGET_H
