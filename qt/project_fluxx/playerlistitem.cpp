#include "playerlistitem.h"

PlayerListItem::PlayerListItem(const ProfileName& name, QWidget *parent) :
    player_name(name), QWidget(parent)
{
    uiElements();
}

PlayerListItem::~PlayerListItem()
{
    delete name_label;
    delete card_count;
    delete keeper_count;
    delete keeper_button;
    delete vertical_layout;
}

int PlayerListItem::getHandCount() const
{
    return hand.size();
}

int PlayerListItem::getKeeperCount() const
{
    return keepers_id.size();
}

void PlayerListItem::updateCards(const std::vector<CardID> hnd, const std::vector<CardID> keeprs)
{
    hand = hnd;
    keepers_id = keeprs;
    card_count->setText(QString{"Hand Count: "} + QString::number(getHandCount()));
    keeper_count->setText(QString{"Keeper Count: "} + QString::number(getKeeperCount()));
    if(getKeeperCount() == 0)
        keeper_button->setEnabled(false);
    else
        keeper_button->setEnabled(true);
}

void PlayerListItem::setActivePlayer()
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::darkGreen);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void PlayerListItem::setNextPlayer()
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::yellow);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void PlayerListItem::setInactivePlayer()
{
    this->setAutoFillBackground(false);
}

void PlayerListItem::mousePressEvent(QMouseEvent* event)
{
    state = true;
    event->accept();
    emit clicked();
}

void PlayerListItem::mouseReleaseEvent(QMouseEvent* event)
{
    state = false;
    event->accept();
    emit clicked();
}

const ProfileName PlayerListItem::getPlayerName() const
{
    return player_name;
}

void PlayerListItem::uiElements()
{
    vertical_layout = new QVBoxLayout();
    name_label = new QLabel(QString{"Player: "} + QString::fromStdString(player_name.val));
    card_count = new QLabel(QString{"Hand Count: "} + QString::number(getHandCount()));
    keeper_count = new QLabel(QString{"Keeper Count: "} + QString::number(getKeeperCount()));
    keeper_button = new QPushButton();

    state = false;

    name_label->setMaximumSize(140, 20);
    card_count->setMaximumSize(140, 20);
    keeper_count->setMaximumSize(140, 20);

    keeper_button->setMinimumSize(140, 23);
    keeper_button->setMaximumSize(140, 23);
    keeper_button->setText(QString{"Keepers"});

    vertical_layout->addWidget(name_label);
    vertical_layout->addWidget(card_count);
    vertical_layout->addWidget(keeper_count);
    vertical_layout->addWidget(keeper_button);

    vertical_layout->setAlignment(name_label, Qt::AlignTop | Qt::AlignCenter);
    vertical_layout->setAlignment(card_count, Qt::AlignTop | Qt::AlignCenter);
    vertical_layout->setAlignment(keeper_count, Qt::AlignTop | Qt::AlignCenter);
    vertical_layout->setAlignment(keeper_button, Qt::AlignTop | Qt::AlignCenter);

    this->setMinimumSize(170, 100);
    this->setMaximumSize(170, 100);

    connectSignals();

    this->setLayout(vertical_layout);
}

void PlayerListItem::connectSignals()
{
    QObject::connect(keeper_button, SIGNAL(clicked()), this, SLOT(showKeepers()));
}

void PlayerListItem::showKeepers()
{
    BigCardCollection* big_keepers = new BigCardCollection(keepers_id, this);
    big_keepers->setWindowTitle(QString::fromStdString(player_name.val) + QString(" keepers"));
    big_keepers->show();
}
