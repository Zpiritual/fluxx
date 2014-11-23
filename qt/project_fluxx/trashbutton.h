#ifndef TRASHBUTTON_H
#define TRASHBUTTON_H

#include <QPushButton>
#include <QtWidgets>
#include <vector>
#include "../../include/CardID.h"

class TrashButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TrashButton(QWidget *parent = 0);
    ~TrashButton();
    void updateCards(std::vector<CardID>);


private:
    std::vector<CardID> cards;
    QIcon* icon;

signals:

public slots:

};

#endif // TRASHBUTTON_H
