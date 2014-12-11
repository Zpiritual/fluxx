//Wrapper for a QEventLoop that will store
//which player the mouse was clicked that stopped the loop

#ifndef PLAYERLOOP_H
#define PLAYERLOOP_H

#include <QEventLoop>
#include "profilename.h"
#include "playerlistitem.h"

class PlayerLoop : public QObject
{
    Q_OBJECT
public:
    explicit PlayerLoop(QObject *parent = 0);
    ProfileName getPlayerName() const;
    void exec();
    bool isRunning() const;
    void exit();

private:
    ProfileName player_name{std::string("tempName")};
    QEventLoop loop;

public slots:
    void quit();
};

#endif // PLAYERLOOP_H
