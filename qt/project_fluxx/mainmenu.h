#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QtWidgets>
#include "profile.h"
#include "Deck.h"
#include "cardpicture.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(const Deck* const, QWidget *parent = 0);
    ~MainMenu();

    void newGame();
    void newGameBack();
    void options();
    void optionsBack();

    void addProfile(const Profile&);
    void setProfiles(const std::vector<Profile>&);

    void writeProfilesToFile() const;

private:
    QVBoxLayout* main_layout; //Main window layout
    QStackedWidget* layouts; //Container for the different menues
    QWidget* start_widget; //The widget that run at start
    QWidget* options_widget; //The options menu widget
    QWidget* newgame_widget; //The newgame menu widget

    std::vector<Profile> profiles;

    const Deck* deck;

signals:

public slots:
};

#endif // MAINMENU_H
