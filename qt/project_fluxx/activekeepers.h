#ifndef ACTIVEKEEPERS_H
#define ACTIVEKEEPERS_H

#include <QWidget>
#include <QtWidgets>
#include "cardbutton.h"
class Gui;


class ActiveKeepers : public QWidget
{
    Q_OBJECT
public:
    explicit ActiveKeepers(QWidget *parent = 0);
    void update();

private:
    QHBoxLayout* layout;
    Gui* guiptr_;


signals:

public slots:

};


#include "gui.h"
#endif // ACTIVEKEEPERS_H
