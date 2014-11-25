#include "bigcardcollection.h"

BigCardCollection::BigCardCollection(const std::vector<CardID>& crds, QWidget *parent) :
    QWidget(parent)
{
    card_collection = new CardCollection(crds);
    scroll_area = new QScrollArea();
    horizontal_layout = new QHBoxLayout();

    horizontal_layout->addWidget(scroll_area);

    scroll_area->setWidget(card_collection);
    scroll_area->setMaximumHeight(265);

    this->setMinimumSize(340,270);
    this->setMaximumSize(340,270);

    this->setWindowTitle("Card Collection");
    this->setLayout(horizontal_layout);
    this->show();
}

BigCardCollection::~BigCardCollection()
{
}

