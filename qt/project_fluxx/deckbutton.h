#ifndef DECKBUTTON_H
#define DECKBUTTON_H

#include <QPushButton>
#include <vector>
#include "CardID.h"
#include "CardContainer.h"

class DeckButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DeckButton(QWidget *parent = 0);
    void updateCards(const CardContainer&);
    ~DeckButton();

private:
      std::vector<CardID> cards_;
      QIcon* icon;

signals:
public slots:

};

#endif // DECKBUTTON_H
