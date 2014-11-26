#include "playerlistitem.h"

PlayerListItem::PlayerListItem(const PlayerID& name, QWidget *parent) :
    player_name(name), QWidget(parent)
{
    vertical_layout = new QVBoxLayout();
    name_label = new QLabel(QString{"Player: "} + QString::fromStdString(player_name.val));
    card_count = new QLabel(QString{"Hand Count: "} + QString::number(getHandCount()));
    keeper_count = new QLabel(QString{"Keeper Count: "} + QString::number(getKeeperCount()));
    keeper_button = new QPushButton();

    name_label->setMaximumSize(140, 20);
    card_count->setMaximumSize(140, 20);
    keeper_count->setMaximumSize(140, 20);

    keeper_button->setMaximumSize(140, 20);
    keeper_button->setText(QString{"Keepers"});

    vertical_layout->addWidget(name_label);
    vertical_layout->addWidget(card_count);
    vertical_layout->addWidget(keeper_count);
    vertical_layout->addWidget(keeper_button);

    vertical_layout->setAlignment(name_label, Qt::AlignTop | Qt::AlignCenter);
    vertical_layout->setAlignment(card_count, Qt::AlignTop | Qt::AlignCenter);
    vertical_layout->setAlignment(keeper_count, Qt::AlignTop | Qt::AlignCenter);
    vertical_layout->setAlignment(keeper_button, Qt::AlignTop | Qt::AlignCenter);

    keepers_id.push_back(CardID{1});
    keepers_id.push_back(CardID{2});
    keepers_id.push_back(CardID{3});

    this->setMinimumSize(170, 100);
    this->setMaximumSize(170, 100);

    QObject::connect(keeper_button, SIGNAL(clicked()), this, SLOT(showKeepers()));

    this->setLayout(vertical_layout);
}

PlayerListItem::~PlayerListItem()
{
    delete vertical_layout;
    delete name_label;
    delete card_count;
    delete keeper_count;
    delete keeper_button;
    delete big_keepers;
}

int PlayerListItem::getHandCount() const
{
    return hand.size();
}

int PlayerListItem::getKeeperCount() const
{
    return keepers_id.size();
}

void PlayerListItem::updateCards(const std::vector<CardID>& hnd, const std::vector<CardID>& keeprs)
{
    hand = hnd;
    keepers_id = keeprs;
    card_count->setText(QString{"Hand Count: "} + QString::number(getHandCount()));
    keeper_count->setText(QString{"Keeper Count: "} + QString::number(getKeeperCount()));
}

void PlayerListItem::setActivePlayer()
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::green);
    this->setGeometry(0, 0, 170, 100);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void PlayerListItem::setNextPlayer()
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::yellow);
    this->setGeometry(0, 0, 170, 100);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

void PlayerListItem::setInactivePlayer()
{
    this->setAutoFillBackground(false);
}


void PlayerListItem::showKeepers()
{
    big_keepers = new BigCardCollection(keepers_id);

    big_keepers->show();
}
