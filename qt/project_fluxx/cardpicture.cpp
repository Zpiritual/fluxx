#include "cardpicture.h"

CardPicture::CardPicture(const Card& card, QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout();
    card_type = new QLabel(QString::fromStdString(card.getType()));
    card_name = new QLabel(QString::fromStdString(card.getName()));
    card_description = new QLabel(QString::fromStdString(card.getDescription()));
    card_id = card.getID();

    layout->addWidget(card_type);
    layout->addWidget(card_name);
    layout->addWidget(card_description);

    layout->setAlignment(card_description, Qt::AlignTop);

    this->setMinimumSize(170, 259);
    this->setMaximumSize(170, 259);

    this->setLayout(layout);
}

CardPicture::~CardPicture()
{
    delete layout;
    delete card_type;
    delete card_name;
    delete card_description;
}

void CardPicture::renderPicture()
{
    QString file_name{":Images/" + QString::number(card_id.val) + ".png"};
    QImage image;

    if(!image.load(file_name))
    {
        QPixmap pixmap(this->rect().size());

        if(card_type->text() == QString("keeper"))
        {
            pixmap.fill(Qt::green);
        }
        else if(card_type->text() == QString("action"))
        {
            pixmap.fill(Qt::blue);
        }
        else if(card_type->text() == QString("goal"))
        {
            pixmap.fill(Qt::red);
        }
        else if(card_type->text() == QString("rule"))
        {
            pixmap.fill(Qt::yellow);
        }

        this->render(&pixmap, QPoint(), QRegion(this->rect()));

        pixmap.save(":Images/" + QString::number(card_id.val) + ".png");
        qDebug() << "New CardPicture created.";
    }
    else
    {
        qDebug() << "CardPicture already exists.";
    }
}
