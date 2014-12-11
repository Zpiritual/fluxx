//This class will create images of cards that exist in the card definition file
//but doesn't have a corresponding image in the image folder

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

    CardID card_id{0};

    void uiElements(const Card&);
};

#endif // CARDPICTURE_H
