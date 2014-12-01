#include "activekeepers.h"

ActiveKeepers::ActiveKeepers(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setMaximumHeight(135);
    this->setMinimumHeight(135);
    this->setMinimumWidth(800);
    this->setLayout(layout);
}

ActiveKeepers::~ActiveKeepers()
{
     for(int i = 0; i < buttons_.size(); i++)
     {
         delete buttons_.at(i);
     }
     delete layout;
}

void ActiveKeepers::update(const CardContainer& container)
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

    std::vector<CardID> cards_{container.getCards()};

    qDebug() << "number of cards to add in rules: " + QString::number(cards_.size());

    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card);
        tempbutton->smallButton();
        layout->addWidget(tempbutton);


        qDebug() << "CardID: " + QString::number(card.val);
        buttons_.push_back(tempbutton);
    }
    std::vector<CardID> cards = container.getCards();
}

void ActiveKeepers::connectButtons(CardIdLoop &loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));

}
