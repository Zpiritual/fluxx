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
    const CardID getCardId();
    void exec();
signals:

public slots:
    void quit();


private:
    int card_button_id;
    QEventLoop loop_;
};

#endif // CARDIDLOOP_H
