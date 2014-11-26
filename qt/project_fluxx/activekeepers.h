#ifndef ACTIVEKEEPERS_H
#define ACTIVEKEEPERS_H

#include <QWidget>
#include <QtWidgets>
#include "cardbutton.h"
#include "CardContainer.h"
#include <vector>

class ActiveKeepers : public QWidget
{
    Q_OBJECT
public:
    explicit ActiveKeepers(QWidget *parent = 0);
    void update(const CardContainer&);
    void connectButtons(QEventLoop& loop);

private:
    QHBoxLayout* layout;
    std::vector<CardButton*> buttons_;

signals:

public slots:

};


#endif // ACTIVEKEEPERS_H
