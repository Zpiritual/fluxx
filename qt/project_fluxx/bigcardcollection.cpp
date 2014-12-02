#include "bigcardcollection.h"

BigCardCollection::BigCardCollection(const std::vector<CardID> crds, QWidget *parent) :
    QWidget(parent)
{
    card_collection = new CardCollection(crds);
    scroll_area = new QScrollArea();
    horizontal_layout = new QHBoxLayout();

    horizontal_layout->addWidget(scroll_area);

    scroll_area->setWidget(card_collection);
    scroll_area->setMaximumHeight(300);

    this->setMinimumSize(550,320);
    this->setMaximumSize(550,320);

    this->setWindowTitle("Card Collection");
    this->setLayout(horizontal_layout);
    this->show();
}

BigCardCollection::BigCardCollection(const std::vector<CardID> crds, CardIdLoop& loop, QWidget *parent) :
    QWidget(parent)
{
    card_collection = new CardCollection(crds, loop);
    scroll_area = new QScrollArea();
    horizontal_layout = new QHBoxLayout();

    horizontal_layout->addWidget(scroll_area);

    scroll_area->setWidget(card_collection);
    scroll_area->setMaximumHeight(300);

    this->setMinimumSize(550,320);
    this->setMaximumSize(550,320);

    this->setWindowTitle("Card Collection");
    this->setLayout(horizontal_layout);
    this->show();
}

BigCardCollection::~BigCardCollection()
{
    delete card_collection;
    delete scroll_area;
    delete horizontal_layout;
}
