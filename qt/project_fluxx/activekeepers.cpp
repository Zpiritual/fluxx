#include "activekeepers.h"

ActiveKeepers::ActiveKeepers(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    for(int i = 66; i <= 70; ++i)
    {
        CardButton* tempbutton = new CardButton(new CardID(i));

        layout->addWidget(tempbutton);
        layout->setAlignment(tempbutton, Qt::AlignCenter|Qt::AlignTop);
    }

    this->setMaximumHeight(259);
    this->setMinimumHeight(259);

    this->setLayout(layout);
}

void ActiveKeepers::update()
{

}
