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

void ActiveHand::updateCards(const CardContainer container)
{
    buttons_.clear();
    this->setAutoFillBackground(false);

   // delete layout;    this->setPalette(QPalette(Qt::green));

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
    }
}

void ActiveHand::connectButtons(CardIdLoop& loop)
{
    this->setAutoFillBackground(true);
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}

void ActiveHand::uiElements()
{
    layout = new QHBoxLayout();
    this->setPalette(QPalette(QPalette::Background, Qt::green));
    this->setMaximumHeight(260);
    this->setMinimumHeight(260);
    this->setLayout(layout);
}
