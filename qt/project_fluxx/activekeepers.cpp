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

void ActiveKeepers::uiElements()
{
    layout = new QHBoxLayout();
    this->setPalette(QPalette(QPalette::Background, Qt::green));
    setContentsMargins(3,3,3,3);
    layout->setSpacing(2);

    this->setMaximumHeight(138);
    this->setMinimumHeight(138);
    this->setLayout(layout);
}


void ActiveKeepers::updateCards(const CardContainer& container)
{
    this->setAutoFillBackground(false);

    //Delete everything in the layout
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
    this->setMaximumWidth(8);

    for(CardID card : cards_) //Add cards to layout
    {
        CardButton* tempbutton = new CardButton(card, this);
        this->setMinimumWidth(this->minimumWidth() + 89);
        this->setMaximumWidth(this->maximumWidth() + 89);

        tempbutton->smallButton();
        layout->addWidget(tempbutton);
        layout->setAlignment(tempbutton, Qt::AlignCenter);
        buttons_.push_back(tempbutton);
    }
    this->setMinimumWidth(this->minimumWidth() + 8);
    this->setMaximumWidth(this->maximumWidth() + 8);
}

void ActiveKeepers::connectButtons(CardIdLoop &loop)
{
    this->setAutoFillBackground(true);
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}

