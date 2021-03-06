#include "cardcollection.h"

CardCollection::CardCollection(const std::vector<CardID>& crds, QWidget *parent) :
    QWidget(parent)
{
    horizontal_layout = new QHBoxLayout();

    addCards(crds);

    this->setLayout(horizontal_layout);
}

CardCollection::CardCollection(const std::vector<CardID>& crds, CardIdLoop &loop, QWidget *parent) :
    QWidget(parent)
{
    horizontal_layout = new QHBoxLayout();

    addCards(crds);

    this->setLayout(horizontal_layout);

    for(auto card : cards)
    {
        QObject::connect(card,SIGNAL(clicked()), &loop, SLOT(quit()));
    }
}

CardCollection::~CardCollection()
{
    for(unsigned int i = 0; i < cards.size(); i++)
    {
        delete cards.at(i);
    }
    delete horizontal_layout;
}

void CardCollection::addCards(const std::vector<CardID>& crds)
{
    for(unsigned int i = 0; i < crds.size(); i++)
    {
        cards.push_back(new CardButton(crds.at(i)));
        horizontal_layout->addWidget(cards.at(i));
    }
}
