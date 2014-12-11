//Class used for the main window. Will swap out it's contents between gameover, start, options and newgame

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QtWidgets>
#include "profile.h"
#include "Deck.h"
#include "cardpicture.h"
#include "SessionData.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(const Deck* const, QWidget *parent = 0);
    ~MainMenu();

    void newGame();
    void newGameBack();//Can be merged with the other back functions
    void options();
    void optionsBack();//Can be merged with the other back functions
    void gameOverBack(); //Can be merged with the other back functions
    void gameOverScreen(SessionData, std::vector<ProfileName>);

    void setProfiles(const std::vector<Profile>&);
    void writeProfilesToFile() const;


    void closeEvent(QCloseEvent*);


private:
    QVBoxLayout* main_layout; //Main window layout
    QWidget* start_widget; //The widget that run at start
    QWidget* options_widget; //The options menu widget
    QWidget* newgame_widget; //The newgame menu widget
    QWidget* game_over_widget; //The game over widget

    std::vector<Profile> profiles;

    const Deck* deck;

    void readProfiles();
    void createPictures() const;
    void addProfile(const Profile&);
    void updateProfiles(const SessionData&);
    void uiElements();
};

#endif // MAINMENU_H
