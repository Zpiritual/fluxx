#include "activehand.h"

ActiveHand::ActiveHand(QWidget *parent) :
    QWidget(parent)
{
    uiElements();    
}

ActiveHand::~ActiveHand()
{
    for(unsigned int i = 0; i < buttons_.size(); i++)
    {
        delete buttons_.at(i);
    }
    delete layout;
}

void ActiveHand::uiElements()
{
    layout = new QHBoxLayout();
    this->setPalette(QPalette(QPalette::Background, Qt::green));
    this->setMaximumHeight(283);
    this->setMinimumHeight(283);
    this->setLayout(layout);
}


void ActiveHand::updateCards(const CardContainer container)
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
    this->setMinimumWidth(10);
    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card, this);
        layout->addWidget(tempbutton);
        layout->setAlignment(tempbutton, Qt::AlignCenter);
        this->setMinimumWidth(this->minimumWidth()+170);
        this->setMaximumWidth(this->maximumWidth()+170);
        buttons_.push_back(tempbutton);
    }
    this->setMinimumWidth(this->minimumWidth()+12);
    this->setMaximumWidth(this->maximumWidth()+12);
}

void ActiveHand::connectButtons(CardIdLoop& loop)
{
    this->setAutoFillBackground(true);
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}

