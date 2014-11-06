#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QtWidgets>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private:
    QVBoxLayout* main_layout;

    QPushButton* new_game_button;
    QPushButton* continue_game_button;
    QPushButton* options_button;
    QPushButton* exit_button;

    void adjust_button_height(int height);
    void adjust_button_width(int width);

signals:

public slots:
    void new_game();
    void continue_game();
    void options();
    void exit();

};

#endif // MAINMENU_H
