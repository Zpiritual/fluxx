#ifndef RULESGRIDWIDGET_H
#define RULESGRIDWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "CardContainer.h"

class Gui;
class CardButton;

class RulesGridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RulesGridWidget(QWidget *parent = 0);
    ~RulesGridWidget();
    void updateCards(const CardContainer&);
    void setConnections(QEventLoop&);

private:
    QGridLayout* layout;
    std::vector<CardID> cards_;
    std::vector<CardButton*> buttons_;
    Gui* guiptr_;

signals:

public slots:

};

#include "cardbutton.h"


#endif // RULESGRIDWIDGET_H
