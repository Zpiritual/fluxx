#include "playerloop.h"

PlayerLoop::PlayerLoop(QObject *parent) :
    QObject(parent)
{
    loop;
}

const ProfileName PlayerLoop::getPlayerName() const
{
    return player_name;
}

void PlayerLoop::exec()
{
    loop.exec();
}

void PlayerLoop::quit()
{
    player_name = dynamic_cast<PlayerListItem*>(sender())->getPlayerName();
    loop.quit();
}
