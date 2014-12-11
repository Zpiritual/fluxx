#include "bigcard.h"

BigCard::BigCard(const CardID* id, QWidget* parent) :
    QGraphicsView(parent)
{
    uiElements(id);   

    this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
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

void BigCard::uiElements(const CardID* id)
{
    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("./Images/"+QString::number(id->val)+".png")));
    scene->addItem(item);

    this->setWindowTitle(QString("Big Card"));
    this->setScene(scene);
}
