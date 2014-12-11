#include "bigcardcollection.h"

BigCardCollection::BigCardCollection(const std::vector<CardID>& crds, QWidget *parent) :
    QWidget(parent)
{
    uiElements(crds);
}

BigCardCollection::BigCardCollection(const std::vector<CardID>& crds, CardIdLoop& loop, QWidget *parent) :
    QWidget(parent)
{
    uiElements(crds, loop);
}

void BigCardCollection::closeEvent(QCloseEvent* event)
{
    event->accept();
    delete this;
}

void BigCardCollection::uiElements(const std::vector<CardID>& crds)
{
    card_collection = new CardCollection(crds);
    scroll_area = new QScrollArea();
    horizontal_layout = new QHBoxLayout();

    horizontal_layout->addWidget(scroll_area);

    scroll_area->setWidget(card_collection);
    scroll_area->setMaximumHeight(300);

    scroll_area->setFrameStyle(QFrame::NoFrame);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog);

    this->setMinimumSize(550,320);
    this->setMaximumSize(550,320);

    this->setWindowTitle("Card Collection");
    this->setLayout(horizontal_layout);
}

void BigCardCollection::uiElements(const std::vector<CardID>& crds, CardIdLoop& loop)
{
    card_collection = new CardCollection(crds, loop);
    scroll_area = new QScrollArea();
    horizontal_layout = new QHBoxLayout();

    this->setPalette(QPalette(QPalette::Background, Qt::green));
    this->setAutoFillBackground(true);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint |Qt::WindowStaysOnTopHint);

    scroll_area->setFrameStyle(QFrame::NoFrame);

    horizontal_layout->addWidget(scroll_area);

    scroll_area->setWidget(card_collection);
    scroll_area->setMaximumHeight(300);

    this->setMinimumSize(550,320);
    this->setMaximumSize(550,320);

    this->setWindowTitle("Card Collection");
    this->setLayout(horizontal_layout);
}

BigCardCollection::~BigCardCollection()
{
    delete card_collection;
    delete scroll_area;
    delete horizontal_layout;
}


