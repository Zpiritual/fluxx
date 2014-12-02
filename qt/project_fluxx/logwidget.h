#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "BoardSnapshot.h"

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();
    void update(const BoardSnapshot* const);

private:
    QLabel* play_info_label;
    QVBoxLayout* layout;
    QTextEdit* log_text_edit;

    void uiElements();

signals:

public slots:

};

#endif // LOGWIDGET_H
