#include "mainmenu.h"
#include "newgame.h"
#include "start.h"
#include "options.h"

#include <fstream>

MainMenu::MainMenu(const Deck* const dck, QWidget *parent) :
    QWidget(parent)
{
    main_layout = new QVBoxLayout();
    start_widget = new Start(this);
    options_widget = NULL;
    newgame_widget = NULL;
    deck = dck;

    this->setWindowTitle(QString("Main Menu"));
    this->setMinimumWidth(640);
    this->setMinimumHeight(480);

    main_layout->addWidget(start_widget);
    this->setLayout(main_layout);

    createPictures();
    readProfiles();
}

MainMenu::~MainMenu()
{
    delete start_widget;
    delete newgame_widget;
    delete options_widget;
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

void MainMenu::addProfile(const Profile& profile)
{
    profiles.push_back(profile);
}

void MainMenu::setProfiles(const std::vector<Profile>& profile_list)
{
    profiles = profile_list;
}

void MainMenu::writeProfilesToFile() const
{
    std::ofstream file("./profiles.txt");
    if(file)
    {
        for(unsigned int i = 0; i < profiles.size(); i++)
        {
            file << profiles.at(i);
        }
    }
    else
    {
        std::cout << "Couldn't open profiles.txt!\n";
    }

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
    // Read in profiles
    std::ifstream file("./profiles.txt");
    Profile p;
    if(file)
    {
        while(file >> p)
        {
            profiles.push_back(p);
        }
    }
    else
    {
        qDebug() << "Couldn't open profiles.txt!\n";
    }
    file.close();
}

void MainMenu::createPictures() const
{
    // Create card pictures if needed
    std::vector<CardID> card_ids = deck->getCardIDList();
    for(unsigned int i = 0; i < card_ids.size(); i++)
    {
        CardPicture card_picture(*(deck->getCard(card_ids.at(i))));
        card_picture.renderPicture();
    }
}
