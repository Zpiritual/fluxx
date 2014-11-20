#include "rulesgridwidget.h"
#include "cardbutton.h"
#include "../../include/CardID.h"


RulesGridWidget::RulesGridWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();

    this->setLayout(layout);
}

RulesGridWidget::~RulesGridWidget(){
}

void RulesGridWidget::updateCards(const CardContainer & container)
{
//    cards = container.getCards();

//    while(!(layout->isEmpty()))
//    {
//        QLayoutItem* temp = layout->itemAt(0);
//        layout->removeItem(temp);
//    }
//    for(auto val : cards)
//    {
//        layout->addWidget(new CardButton(val));
//    }
}
