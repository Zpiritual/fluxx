//This is the class used for all of the cards in gui and in the popup windows.

#ifndef CARDBUTTON_H
#define CARDBUTTON_H

#include <QPushButton>
#include "CardID.h"
#include <bigcard.h>
#include <QMouseEvent>
#include <QDebug>

class CardButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CardButton(const CardID&, QWidget *parent = 0);
    ~CardButton();

    void smallButton();
    const CardID& getCardId() const;

protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    unsigned card_id;
    QIcon* icon;
    CardID* id_;

    void uiElements(const CardID&);

signals:
    void rightClicked();


};

#endif // CARD_H
