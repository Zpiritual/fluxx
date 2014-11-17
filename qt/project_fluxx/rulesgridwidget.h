#ifndef RULESGRIDWIDGET_H
#define RULESGRIDWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "card.h"

class RulesGridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RulesGridWidget(QWidget *parent = 0);
    ~RulesGridWidget();

private:
    QGridLayout* layout;
    Card* card_1;

signals:

public slots:

};

#endif // RULESGRIDWIDGET_H
