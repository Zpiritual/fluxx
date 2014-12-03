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
    QHBoxLayout* layout;
    std::vector<CardID> cards_;
    std::vector<CardButton*> buttons_;

    void uiElements();

signals:

public slots:

};



#endif // RULESGRIDWIDGET_H
