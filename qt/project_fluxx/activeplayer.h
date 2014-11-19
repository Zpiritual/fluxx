#ifndef ACTIVEPLAYER_H
#define ACTIVEPLAYER_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include "../../include/PlayerID.h"

class ActivePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit ActivePlayer(QWidget *parent = 0);
    ~ActivePlayer();

private:
    QListWidget* hand_list;
    QHBoxLayout* layout;
    std::vector<QListWidgetItem*> hand_list_items;

signals:

public slots:

};

#endif // ACTIVEPLAYER_H
