#ifndef CARD_H
#define CARD_H

#include <QPushButton>

class Card : public QPushButton
{
    Q_OBJECT
public:
    explicit Card(int id, QWidget *parent = 0);
    ~Card();
    unsigned getCardId();


private:
    unsigned card_id;
signals:

public slots:

};

#endif // CARD_H
