#include "rulesgridwidget.h"
#include "cardbutton.h"
#include "../../include/CardID.h"


RulesGridWidget::RulesGridWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();
    for(int i = 0; i<= 3; ++i)
        layout->setColumnMinimumWidth(i,170);

    for(int i =  1; i <= 5; ++i)
    {
        layout->addWidget(new CardButton(CardID(i)), i/4,(i-1)%4);
    }

    this->setLayout(layout);
}

RulesGridWidget::~RulesGridWidget(){
}

void RulesGridWidget::updateCards(const CardContainer & container)
{
    cards_ = container.getCards();

    while(!(layout->isEmpty()))
    {
        QLayoutItem* temp = layout->itemAt(0);
        layout->removeItem(temp);
    }
    for(auto card : cards_)
    {
        layout->addWidget(new CardButton(card));
    }
}
