#include "activeplayer.h"
#include <vector>

ActivePlayer::ActivePlayer(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();
    hand_list = new QListWidget();

    layout->addWidget(hand_list);

    hand_list->setFlow(QListView::LeftToRight);

    for(int i=1; i <= 7; ++i)
    {
        QString temp_string{":Images/"+QString::number(i)+".png"};
        qDebug() << "Int:" << temp_string;

        hand_list_items.push_back(new QListWidgetItem(QIcon(temp_string), "", hand_list));
    }

    for(auto c : hand_list_items)
        hand_list->addItem(c);

    hand_list->setIconSize(QSize(156,239));
    hand_list->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    this->setMinimumHeight(280);
    this->setMaximumHeight(280);
    this->setLayout(layout);
}

ActivePlayer::~ActivePlayer(){
}
