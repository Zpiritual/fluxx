#include "activekeepers.h"

ActiveKeepers::ActiveKeepers(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();
    guiptr_ = dynamic_cast<Gui*>(parent);

//    for(int i = 66; i <= 70; ++i)
//    {
//        CardButton* tempbutton = new CardButton(new CardID(i,guiptr_));
//        tempbutton->smallButton();
//        layout->addWidget(tempbutton);
//        layout->setAlignment(tempbutton, Qt::AlignCenter|Qt::AlignTop);
//    }

    this->setMaximumHeight(135);
    this->setMinimumHeight(135);

    this->setLayout(layout);
}

void ActiveKeepers::update()
{

}
