#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QtWidgets>

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = 0);

private:
    QTextEdit* user_profles;

    QPushButton* done_button;
    QPushButton* cancel_button;

signals:

public slots:

};

#endif // OPTIONS_H
