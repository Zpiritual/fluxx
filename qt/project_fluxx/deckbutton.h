#ifndef DECKBUTTON_H
#define DECKBUTTON_H

#include <QPushButton>
#include <vector>
#include "../../include/CardID.h"

class DeckButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DeckButton(QWidget *parent = 0);
    void updateCards(const std::vector<CardID>&);
    ~DeckButton();

private:
      std::vector<CardID> cards;
      QIcon* icon;

signals:

public slots:

};

#endif // DECKBUTTON_H
