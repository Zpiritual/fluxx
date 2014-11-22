#ifndef CARD_H
#define CARD_H

#include <QPushButton>
#include <../../include/CardID.h>

class CardButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CardButton(CardID id, QWidget *parent = 0);
    ~CardButton();
    unsigned getCardId() const;

protected:
    void mouseReleaseEvent(QMouseEvent *e);
private:
    unsigned card_id;
    QIcon* icon;
signals:
    void rightClicked();
public slots:

};

#endif // CARD_H
