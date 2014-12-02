#include "bigcard.h"

BigCard::BigCard(CardID* id, QWidget *parent) :
    QWidget(parent)
{
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("./Images/"+QString::number(id->val)+".png")));
    scene->addItem(item);

    view->setWindowTitle(QString("Big Card"));
    view->show();
}
