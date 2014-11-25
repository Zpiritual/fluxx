#ifndef RULESGRIDWIDGET_H
#define RULESGRIDWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "CardContainer.h"


class CardButton;

class RulesGridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RulesGridWidget(QWidget *parent = 0);
    ~RulesGridWidget();
    void updateCards(const CardContainer&);

private:
    QGridLayout* layout;
    std::vector<CardID> cards_;

signals:

public slots:

};

#include "cardbutton.h"


#endif // RULESGRIDWIDGET_H
