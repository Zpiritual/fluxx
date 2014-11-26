#include "rulesgridwidget.h"


RulesGridWidget::RulesGridWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();
    for(int i = 0; i<= 3; ++i)
    {
        layout->setColumnMinimumWidth(i,170);
        layout->setColumnStretch(i, 0);
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
        CardButton* tempbutton = new CardButton(card);
        layout->addWidget(tempbutton);
        buttons_.push_back(tempbutton);
    }
}

void RulesGridWidget::setConnections(QEventLoop & loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}
