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
    const ProfileName getPlayerName() const;
    void exec();
    const bool isRunning() const;
    void exit();

private:
    ProfileName player_name{std::string("tempName")};
    QEventLoop loop;

signals:

public slots:
    void quit();
};

#endif // PLAYERLOOP_H
