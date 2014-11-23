#ifndef RULESGRIDWIDGET_H
#define RULESGRIDWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "cardbutton.h"
#include <vector>
#include "CardContainer.h"



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

#endif // RULESGRIDWIDGET_H
