//This is a wrapper of a QEventloop that also store the cardid of the card that stopped the loop.

#ifndef CARDIDLOOP_H
#define CARDIDLOOP_H

#include <QEventLoop>
#include "CardID.h"
#include "cardbutton.h"

class CardIdLoop : public QObject
{
    Q_OBJECT
public:
    explicit CardIdLoop(QObject *parent = 0);
    CardID getCardId();
    bool isRunning() const;
    void exec();
    void exit();

public slots:
    void quit();

private:
    int card_button_id;
    QEventLoop loop_;
};

#endif // CARDIDLOOP_H
