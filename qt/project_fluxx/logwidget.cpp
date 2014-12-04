#include "logwidget.h"

LogWidget::LogWidget(const std::vector<ProfileName> names, QWidget *parent) :
    QWidget(parent)
{
    player_names = names;
    uiElements();
}

LogWidget::~LogWidget()
{
    delete log_text_edit;
    delete play_info_label;
    delete layout;
}

void LogWidget::updateLog(const BoardSnapshot* const snapshot)
{
//    std::string tempstring;
    log_text_edit->setText(QString(""));
    int i = 0;
    for(const std::pair<const PlayerID, const std::string> entry : snapshot->log)
    {
        ProfileName player = player_names.at(entry.first.getInt()-1);
        QString tempstring = log_text_edit->toPlainText();
        if(i++ != 0)
        {
            tempstring += QString("\n");
        }
        tempstring += QString::fromStdString(player.val) + QString(" turn\n") + QString::fromStdString(entry.second) ;
        log_text_edit->setPlainText(tempstring);
    }
  //  log_text_edit->verticalScrollBar()->setValue(log_text_edit->verticalScrollBar()->maximum());

    play_info_label->setText(QString("Cards to play:" + QString::number(snapshot->cards_to_play) + QString("\nCards played:" + QString::number(snapshot->cards_played))));

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

    this->setMaximumWidth(180);

    log_text_edit->setReadOnly(true);
    log_text_edit->setTextInteractionFlags(Qt::NoTextInteraction);

    this->setLayout(layout);
}

