#ifndef BIGCARD_H
#define BIGCARD_H

#include <QWidget>
#include "../../include/CardID.h"
#include <QtWidgets>

class BigCard : public QWidget
{
    Q_OBJECT
public:
    explicit BigCard(CardID*, QWidget *parent = 0);

signals:

public slots:

};

#endif // BIGCARD_H
