#include "rulesgridwidget.h"
#include "cardbutton.h"
#include "../../include/CardID.h"


RulesGridWidget::RulesGridWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();
    card_1 = new CardButton(CardID{1});

    card_1->setMinimumSize(156,239);

    layout->addWidget(card_1);
    card_1->setIconSize(QSize(156,239));
    card_1->setMaximumSize(156,239);

    this->setLayout(layout);
}

RulesGridWidget::~RulesGridWidget(){
}
