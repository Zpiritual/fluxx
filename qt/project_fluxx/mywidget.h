#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtWidgets>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private:
    QGridLayout* mainLayout;
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout;

    QPushButton* newGameButton;
    QPushButton* continueGameButton;
    QPushButton* optionsButton;
    QPushButton* exitButton;

signals:

public slots:
    void newGame();
    void continueGame();
    void options();
    void exit();
    void changeExitLayout();
};

#endif // MYWIDGET_H
