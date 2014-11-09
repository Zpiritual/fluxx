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

    void newGame();
    void newGameBack();
   // void options();
  //  void optionsBack();

private:
    QVBoxLayout* main_layout; //Main window layout
    QStackedWidget* layouts; //Container for the different menues
    QWidget* start_widget; //The widget that run at start
    QWidget* options_widget; //The options menu widget
    QWidget* newgame_widget; //The newgame menu widget

signals:

public slots:
};

#endif // MAINMENU_H
