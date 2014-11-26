#include "cardcollection.h"

CardCollection::CardCollection(const std::vector<CardID>& crds, QWidget *parent) :
    QWidget(parent)
{
    horizontal_layout = new QHBoxLayout();

    for(int i = 0; i < crds.size(); i++)
    {
        cards.push_back(new CardButton(crds.at(i)));
        horizontal_layout->addWidget(cards.at(i));
    }

    this->setLayout(horizontal_layout);
}

CardCollection::~CardCollection()
{
    for(int i = 0; i < cards.size(); i++)
    {
        delete cards.at(i);
    }

    delete horizontal_layout;
}
