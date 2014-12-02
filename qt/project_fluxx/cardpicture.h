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

    void renderPicture();

private:
    QVBoxLayout* layout;
    QLabel* card_type;
    QLabel* card_name;
    QTextEdit* card_description;

    CardID card_id{-1};


signals:

public slots:

};

#endif // CARDPICTURE_H
