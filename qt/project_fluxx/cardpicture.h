#ifndef CARDPICTURE_H
#define CARDPICTURE_H

#include <QWidget>
#include <QtWidgets>
#include "Card.h"

class CardPicture : public QWidget
{
    Q_OBJECT
public:
    explicit CardPicture(const Card&, QWidget *parent = 0);
    ~CardPicture();

    void render() const;

private:
    QVBoxLayout* layout;
    QLabel* card_type;
    QLabel* card_name;
    QLabel* card_description;

    CardID card_id;


signals:

public slots:

};

#endif // CARDPICTURE_H
