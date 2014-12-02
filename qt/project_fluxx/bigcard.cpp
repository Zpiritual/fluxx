#include "bigcard.h"

BigCard::BigCard(CardID* id, QWidget* parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene(parent);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("./Images/"+QString::number(id->val)+".png")));
    scene->addItem(item);

    this->setWindowTitle(QString("Big Card"));
    this->setScene(scene);
}

BigCard::~BigCard()
{
    delete item;
    delete scene;
}

void BigCard::closeEvent(QCloseEvent* event)
{
    event->accept();
    delete this;
}
