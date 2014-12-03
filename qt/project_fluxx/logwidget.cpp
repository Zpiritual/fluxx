#include "logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
}

LogWidget::~LogWidget()
{
    delete log_text_edit;
    delete play_info_label;
    delete layout;
}

void LogWidget::update(const BoardSnapshot* const board)
{
    play_info_label->setText(QString("Cards to play:" + QString::number(board->cards_to_play) + QString("\nCards played:" + QString::number(board->cards_played))));

    // TODO: Add log from boardsnapshot
    //log_text_edit->setText();
}

void LogWidget::uiElements()
{
    layout = new QVBoxLayout();
    log_text_edit = new QTextEdit();
    play_info_label = new QLabel();

    play_info_label->setText(QString("Play Info Here"));

    log_text_edit->setText(QString("Log Text Here"));
    layout->addWidget(log_text_edit);
    layout->addWidget(play_info_label);

    this->setMaximumWidth(160);

    log_text_edit->setReadOnly(true);
    log_text_edit->setTextInteractionFlags(Qt::NoTextInteraction);

     this->setLayout(layout);
}

