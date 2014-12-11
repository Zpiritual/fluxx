//Class that shows the log and info about how many cards should be and have been play

#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "BoardSnapshot.h"
#include "profilename.h"

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(const std::vector<ProfileName>, QWidget *parent = 0);
    ~LogWidget();
    void updateLog(const BoardSnapshot* const);

private:
    QLabel* play_info_label;
    QVBoxLayout* layout;
    QTextEdit* log_text_edit;
    std::vector<ProfileName> player_names;

    void uiElements();
};

#endif // LOGWIDGET_H
