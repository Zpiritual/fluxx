#include "rulesgridwidget.h"


RulesGridWidget::RulesGridWidget(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
}

RulesGridWidget::~RulesGridWidget()
{
    for(unsigned int i = 0; i < buttons_.size(); i++)
    {
        delete buttons_.at(i);
    }
    delete layout;
}

void RulesGridWidget::updateCards(const CardContainer container)
{
    buttons_.clear();

   // delete layout;

    if (layout->layout() != NULL)
    {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }
       // delete layout->layout();
    }
    this->setMinimumWidth(0);

    std::vector<CardID> cards_{container.getCards()};

    qDebug() << "number of cards to add in rules: " + QString::number(cards_.size());

    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card);
        layout->addWidget(tempbutton);
        this->setMinimumWidth(this->minimumWidth()+160);
        qDebug() << "CardID: " + QString::number(card.val);
        buttons_.push_back(tempbutton);
    }}

void RulesGridWidget::setConnections(CardIdLoop & loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}

void RulesGridWidget::uiElements()
{
    layout = new QHBoxLayout();

    this->setMinimumHeight(270);
    this->setMaximumHeight(270);

    this->setLayout(layout);
}
