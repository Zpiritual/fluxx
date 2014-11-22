#ifndef ACTIVEKEEPERS_H
#define ACTIVEKEEPERS_H

#include <QWidget>
#include <QtWidgets>
#include "cardbutton.h"

class ActiveKeepers : public QWidget
{
    Q_OBJECT
public:
    explicit ActiveKeepers(QWidget *parent = 0);
    void update();

private:
    QHBoxLayout* layout;

signals:

public slots:

};

#endif // ACTIVEKEEPERS_H
