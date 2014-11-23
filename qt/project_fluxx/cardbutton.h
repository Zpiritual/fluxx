#ifndef CARD_H
#define CARD_H

#include <QPushButton>
#include "CardID.h"
#include <bigcard.h>
#include <QMouseEvent>
#include <QDebug>

class CardButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CardButton(CardID, QWidget *parent = 0);
    explicit CardButton(CardID*, QWidget *parent = 0);
    ~CardButton();
    unsigned getCardId() const;

protected:
    void mouseReleaseEvent(QMouseEvent *e);
private:
    unsigned card_id;
    QIcon* icon;
    CardID* id_;
signals:
    void rightClicked();
public slots:

};

#endif // CARD_H
