#include "activekeepers.h"

ActiveKeepers::ActiveKeepers(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
}

ActiveKeepers::~ActiveKeepers()
{
     for(unsigned int i = 0; i < buttons_.size(); i++)
     {
         delete buttons_.at(i);
     }
     delete layout;
}

void ActiveKeepers::updateCards(const CardContainer& container)
{
    this->setAutoFillBackground(false);
    buttons_.clear();

    if (layout->layout() != NULL)
    {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }
    }

    std::vector<CardID> cards_{container.getCards()};

    this->setMinimumWidth(8);
    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card, this);
        this->setMinimumWidth(this->minimumWidth() + 89 );
        tempbutton->smallButton();
        layout->addWidget(tempbutton);
        buttons_.push_back(tempbutton);
    }
    this->setMinimumWidth(this->minimumWidth() + 8);
}

void ActiveKeepers::connectButtons(CardIdLoop &loop)
{
    this->setAutoFillBackground(true);
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));

}

void ActiveKeepers::uiElements()
{
    layout = new QHBoxLayout();
    this->setPalette(QPalette(QPalette::Background, Qt::green));

    this->setMaximumHeight(135);
    this->setMinimumHeight(135);
    this->setLayout(layout);
}
