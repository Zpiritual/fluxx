#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QtWidgets>

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();

private:
    QLabel* log_label;
    QVBoxLayout* layout;

signals:

public slots:

};

#endif // LOGWIDGET_H
