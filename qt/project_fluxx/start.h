//The screen shown when the main menu starts.

#ifndef START_H
#define START_H

#include <QWidget>
#include <QtWidgets>
#include "mainmenu.h"


class Start : public QWidget
{
    Q_OBJECT
public:
    explicit Start(QWidget *parent = 0);
    ~Start();

private:
    QVBoxLayout* layout;
    QPushButton* new_game_button;
    QPushButton* options_button;
    QPushButton* exit_button;
    MainMenu* parent2;

    void adjust_button_height(int height);
    void adjust_button_width(int width);

    void connectSignals();
    void uiElements();

    void message(const QString&, const QString&) const;

public slots:
    void new_game();
    void options();
    void exit();

};

#endif // START_H
