#ifndef TRASHBUTTON_H
#define TRASHBUTTON_H

#include <QPushButton>
#include <QtWidgets>
#include <vector>
#include "CardID.h"
#include "CardContainer.h"
#include "cardidloop.h"
#include "bigcardcollection.h"

class TrashButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TrashButton(QWidget *parent = 0);
    ~TrashButton();
    void updateCards(const CardContainer&);
    void setConnections(CardIdLoop&);
private:
    std::vector<CardID> cards_;
    QIcon* icon;

signals:

public slots:
    void clickbutton();
};

#endif // TRASHBUTTON_H
