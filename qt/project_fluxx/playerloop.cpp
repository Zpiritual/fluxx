#include "playerloop.h"

PlayerLoop::PlayerLoop(QObject *parent) :
    QObject(parent)
{
}

ProfileName PlayerLoop::getPlayerName() const
{
    return player_name;
}

void PlayerLoop::exec()
{
    loop.exec();
}

bool PlayerLoop::isRunning() const
{
    return loop.isRunning();
}

void PlayerLoop::exit()
{
    loop.exit();
}

void PlayerLoop::quit()
{
    if(loop.isRunning())
    {
        player_name = dynamic_cast<PlayerListItem*>(sender())->getPlayerName();
        loop.quit();
    }
}
