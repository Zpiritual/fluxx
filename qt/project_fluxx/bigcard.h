#ifndef BIGCARD_H
#define BIGCARD_H

#include <QWidget>
#include "CardID.h"
#include <QtWidgets>

class BigCard : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BigCard(CardID*, QWidget* parent = 0);
    ~BigCard();

    void closeEvent(QCloseEvent*);

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* item;

signals:

public slots:

};

#endif // BIGCARD_H
