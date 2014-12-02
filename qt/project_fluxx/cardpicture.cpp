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

    layout->setAlignment(card_type, Qt::AlignTop | Qt::AlignCenter);
    layout->setAlignment(card_name, Qt::AlignTop | Qt::AlignCenter);
    layout->setAlignment(card_description, Qt::AlignTop | Qt::AlignCenter);

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

        QPalette Pal(palette());

        if(card_type->text().toLower() == QString("keeper"))
        {
            Pal.setColor(QPalette::Background, QColor(100, 255, 75));
        }
        else if(card_type->text().toLower() == QString("action"))
        {
            Pal.setColor(QPalette::Background, QColor(130, 130, 255));
        }
        else if(card_type->text().toLower() == QString("goal"))
        {
            Pal.setColor(QPalette::Background, QColor(255, 100, 100));
        }
        else if(card_type->text().toLower() == QString("rule"))
        {
            Pal.setColor(QPalette::Background, QColor(220, 255, 100));
        }

        this->setAutoFillBackground(true);
        this->setPalette(Pal);

        this->render(&pixmap, QPoint(), QRegion(this->rect()));

        pixmap.save("./Images/" + QString::number(card_id.val) + ".png");
        qDebug() << "New CardPicture created.";
    }
}
