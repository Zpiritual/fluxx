#include "playerlistitem.h"

PlayerListItem::PlayerListItem(const PlayerID& name, QWidget *parent) :
    player_name(name), QWidget(parent)
{
    vertical_layout = new QVBoxLayout();
    name_label = new QLabel(QString{"Player: "} + QString::fromStdString(player_name.val));
    card_count = new QLabel(QString{"Hand Count: "} + QString::number(getHandCount()));
    keeper_count = new QLabel(QString{"Keeper Count: "} + QString::number(getKeeperCount()));
    keeper_button = new QPushButton();

    keeper_button->setText(QString{"Keepers"});

    vertical_layout->addWidget(name_label);
    vertical_layout->addWidget(card_count);
    vertical_layout->addWidget(keeper_count);
    vertical_layout->addWidget(keeper_button);

    vertical_layout->setAlignment(name_label, Qt::AlignCenter);
    vertical_layout->setAlignment(card_count, Qt::AlignCenter);
    vertical_layout->setAlignment(keeper_count, Qt::AlignCenter);
    vertical_layout->setAlignment(keeper_button, Qt::AlignCenter);

    keepers_id.push_back(CardID{1});
    keepers_id.push_back(CardID{2});
    keepers_id.push_back(CardID{3});

    QObject::connect(keeper_button, SIGNAL(clicked()), this, SLOT(showKeepers()));

    this->setLayout(vertical_layout);
    this->show();
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

void PlayerListItem::showKeepers()
{
    BigCardCollection* big_keepers = new BigCardCollection(keepers_id);

    big_keepers->show();
}
