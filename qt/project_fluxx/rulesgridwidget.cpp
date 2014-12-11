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

    this->setAutoFillBackground(false);

    if (layout->layout() != NULL)
    {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }
    }
    this->setMinimumWidth(0);
    this->setMaximumWidth(0);

    std::vector<CardID> cards_{container.getCards()};

    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card);
        layout->addWidget(tempbutton);
        this->setMinimumWidth(this->minimumWidth()+170);
        this->setMaximumWidth(this->maximumWidth()+170);
        buttons_.push_back(tempbutton);
    }
    this->setMinimumWidth(this->minimumWidth()+12);
    this->setMaximumWidth(this->maximumWidth()+12);

}

void RulesGridWidget::setConnections(CardIdLoop & loop)
{
    this->setAutoFillBackground(true);
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}

void RulesGridWidget::uiElements()
{
    layout = new QHBoxLayout();

    this->setPalette(Qt::green);
    this->setMinimumHeight(270);
    this->setMaximumHeight(270);

    this->setLayout(layout);
}
