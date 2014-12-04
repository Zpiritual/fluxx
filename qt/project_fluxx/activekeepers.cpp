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

    qDebug() << "number of cards to add in keepers: " + QString::number(cards_.size());

    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card);
        tempbutton->smallButton();
        layout->addWidget(tempbutton);
        buttons_.push_back(tempbutton);
    }
    std::vector<CardID> cards = container.getCards();
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
    this->setMinimumWidth(800);
    this->setLayout(layout);
}
