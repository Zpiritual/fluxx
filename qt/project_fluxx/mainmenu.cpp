#include "mainmenu.h"
#include "newgame.h"
#include "start.h"
#include "options.h"
#include "gameover.h"


#include <fstream>

MainMenu::MainMenu(const Deck* const dck, QWidget *parent) :
    QWidget(parent)
{
    deck = dck;
    uiElements();
    createPictures();
    readProfiles();
}

MainMenu::~MainMenu()
{
    delete deck;
    delete start_widget;
    delete newgame_widget;
    delete options_widget;
    delete game_over_widget;
    delete main_layout;
}

void MainMenu::newGame()
{
    newgame_widget = new NewGame(profiles, deck, this);
    main_layout->addWidget(newgame_widget);
    main_layout->removeWidget(start_widget);
    this->setWindowTitle(QString("New Game"));

    delete start_widget;
    start_widget = NULL;
}

void MainMenu::newGameBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(newgame_widget);
    this->setWindowTitle(QString("Main Menu"));

    delete newgame_widget;
    newgame_widget = NULL;
}

void MainMenu::options()
{
    options_widget = new Options(profiles, this);
    main_layout->addWidget(options_widget);
    main_layout->removeWidget(start_widget);
    this->setWindowTitle(QString("Options"));

    delete start_widget;
    start_widget = NULL;
}

void MainMenu::optionsBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(options_widget);
    this->setWindowTitle(QString("Main Menu"));

    delete options_widget;
    options_widget = NULL;
}

void MainMenu::gameOverBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(game_over_widget);
    this->setWindowTitle(QString("Main menu"));

    delete game_over_widget;
    game_over_widget = NULL;
}

void MainMenu::gameOverScreen(SessionData session_data, std::vector<ProfileName> players)
{
    game_over_widget = new GameOver(session_data, players, this);
    main_layout->addWidget(game_over_widget);
    main_layout->removeWidget(newgame_widget);
    this->setWindowTitle(QString("Game Over"));

    updateProfiles(session_data);

    delete newgame_widget;
    newgame_widget = NULL;

    qDebug() << "game over screen in main menu done";
}

void MainMenu::addProfile(const Profile& profile)
{
    profiles.push_back(profile);
}

void MainMenu::setProfiles(const std::vector<Profile>& profile_list)
{
    profiles = profile_list;
}

void MainMenu::updateProfiles(const SessionData& session_data)
{
    for(unsigned int i = 0; i < session_data.players.size(); i++)
    {
        profiles.at(session_data.players.at(i)._id.getInt() - 1) += session_data.players.at(i);
        profiles.at(session_data.players.at(i)._id.getInt() - 1).setPlayTime(profiles.at(session_data.players.at(i)._id.getInt() - 1).getPlayTime() + session_data.elapsed_time);
        if(profiles.at(session_data.players.at(i)._id.getInt() - 1).getMaxConsecutivePlays() < session_data.players.at(i)._max_consecutive_plays)
            profiles.at(session_data.players.at(i)._id.getInt() - 1).setMaxConsecutivePlays(session_data.players.at(i)._max_consecutive_plays);
    }
    profiles.at(session_data.winning_player.getInt() - 1).setWins(profiles.at(session_data.winning_player.getInt() - 1).getWins() + 1);
}

void MainMenu::uiElements()
{
    main_layout = new QVBoxLayout();
    start_widget = new Start(this);
    options_widget = NULL;
    newgame_widget = NULL;
    game_over_widget = NULL;

    this->setWindowTitle(QString("Main Menu"));
    this->setFixedSize(640,480);
    this->setLayout(main_layout);
    this->setWindowFlags(Qt::Dialog);

    main_layout->addWidget(start_widget);

}

void MainMenu::writeProfilesToFile() const
{
    std::ofstream file("./profiles.txt");
    if(file)
    {
        for(unsigned int i = 0; i < profiles.size(); i++)
            file << profiles.at(i);
    }
    else
        std::cout << "Couldn't open profiles.txt!\n";
    file.close();
}

void MainMenu::closeEvent(QCloseEvent* event)
{
    writeProfilesToFile();
    event->accept();
    delete this;
}

void MainMenu::readProfiles()
{
    std::ifstream file("./profiles.txt");
    Profile p;
    if(file)
    {
        while(file >> p)
            profiles.push_back(p);
    }
    else
        qDebug() << "Couldn't open profiles.txt!\n";
    file.close();
}

void MainMenu::createPictures() const
{
    std::vector<CardID> card_ids = deck->getCardIDList();
    for(unsigned int i = 0; i < card_ids.size(); i++)
    {
        CardPicture card_picture(*(deck->getCard(card_ids.at(i))));
        card_picture.renderPicture();
    }
}
