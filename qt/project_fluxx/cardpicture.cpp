#include "cardpicture.h"

CardPicture::CardPicture(const Card& card, QWidget *parent) :
    QWidget(parent)
{
    uiElements(card);
}

CardPicture::~CardPicture()
{
    delete card_type;
    delete card_name;
    delete card_description;
    delete layout;
}

void CardPicture::renderPicture()
{
    QString file_name{"./Images/" + QString::number(card_id.val) + ".png"};
    QImage image;

    if(!image.load(file_name))
    {
        QPixmap pixmap(this->rect().size());

        QPalette pal(palette());
        QPalette pal_log(palette());

        if(card_type->text().toLower() == QString("keeper"))
        {
            pal.setColor(QPalette::Background, QColor(100, 255, 75));
            pal_log.setColor(QPalette::Base, QColor(100, 255, 75));
        }
        else if(card_type->text().toLower() == QString("action"))
        {
            pal.setColor(QPalette::Background, QColor(130, 130, 255));
            pal_log.setColor(QPalette::Base, QColor(130, 130, 255));
        }
        else if(card_type->text().toLower() == QString("goal"))
        {
            pal.setColor(QPalette::Background, QColor(255, 100, 100));
            pal_log.setColor(QPalette::Base, QColor(255, 100, 100));
        }
        else if(card_type->text().toLower() == QString("rule"))
        {
            pal.setColor(QPalette::Background, QColor(220, 255, 100));
            pal_log.setColor(QPalette::Base, QColor(220, 255, 100));
        }

        this->setAutoFillBackground(true);
        this->setPalette(pal);
        card_description->setPalette(pal_log);

        this->render(&pixmap, QPoint(), QRegion(this->rect()));

        pixmap.save("./Images/" + QString::number(card_id.val) + ".png");
        qDebug() << "New CardPicture created.";
    }
}

void CardPicture::uiElements(const Card& card)
{
    layout = new QVBoxLayout();
    card_type = new QLabel(QString::fromStdString(card.getType()));
    card_name = new QLabel(QString::fromStdString(card.getName()));
    card_description = new QTextEdit(QString::fromStdString(card.getDescription()));
    card_id = card.getID();

    layout->addWidget(card_type);
    layout->addWidget(card_name);
    layout->addWidget(card_description);

    layout->setAlignment(card_type, Qt::AlignTop | Qt::AlignCenter);
    layout->setAlignment(card_name, Qt::AlignTop | Qt::AlignCenter);
    layout->setAlignment(card_description, Qt::AlignTop | Qt::AlignCenter);

    card_description->setFrameStyle(QFrame::NoFrame);
    card_description->setFont(QFont("arial", 12));

    this->setMinimumSize(250, 381);
    this->setMaximumSize(250, 381);

    this->setLayout(layout);
}
