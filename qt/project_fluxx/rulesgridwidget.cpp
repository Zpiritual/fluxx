#include "rulesgridwidget.h"


RulesGridWidget::RulesGridWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();
    for(int i = 0; i<= 5; ++i)
    {
        layout->setColumnMinimumWidth(i,175);

    }
    layout->setRowMinimumHeight(0,260);
    layout->setRowMinimumHeight(1,260);
    layout->setSpacing(0);
    this->setLayout(layout);
}

RulesGridWidget::~RulesGridWidget(){
}

void RulesGridWidget::updateCards(const CardContainer container)
{
    buttons_.clear();

   // delete layout;

    if ( layout->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = layout->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
       // delete layout->layout();
    }
    std::vector<CardID> cards_{container.getCards()};

    qDebug() << "number of cards to add in rules: " + QString::number(cards_.size());

    int row{};
    int column{};

    for(CardID card : cards_)
    {
        CardButton* tempbutton = new CardButton(card);
        layout->addWidget(tempbutton,row, column);

        buttons_.push_back(tempbutton);
        ++ column;
        if(column >=5) //number of columns
        {
            column = 0;
            ++row;
        }
    }
}

void RulesGridWidget::setConnections(CardIdLoop & loop)
{
    for(auto button : buttons_)
        QObject::connect(button,SIGNAL(clicked()), &loop, SLOT(quit()));
}
