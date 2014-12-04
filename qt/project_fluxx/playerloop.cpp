#include "playerloop.h"

PlayerLoop::PlayerLoop(QObject *parent) :
    QObject(parent)
{
}

const ProfileName PlayerLoop::getPlayerName() const
{
    return player_name;
}

void PlayerLoop::exec()
{
    loop.exec();
}

const bool PlayerLoop::isRunning() const
{
    return loop.isRunning();
}

void PlayerLoop::quit()
{
    if(loop.isRunning())
    {
        player_name = dynamic_cast<PlayerListItem*>(sender())->getPlayerName();
        loop.quit();
    }
}
