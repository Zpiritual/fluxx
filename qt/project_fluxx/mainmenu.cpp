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
    deck = dck;

    this->setWindowTitle(QString("Main Menu"));
    this->setMinimumWidth(640);
    this->setMinimumHeight(480);

    main_layout->addWidget(start_widget);
    this->setLayout(main_layout);

    // Create card pictures if needed
    std::vector<CardID> card_ids = deck->getCardIDList();
    for(int i = 0; i < card_ids.size(); i++)
    {
        CardPicture card_picture(*(deck->getCard(card_ids.at(i))));
        card_picture.renderPicture();
    }

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

MainMenu::~MainMenu()
{
    delete start_widget;
    delete main_layout;
}

void MainMenu::newGame()
{
    newgame_widget = new NewGame(profiles, deck, this);
    main_layout->addWidget(newgame_widget);
    main_layout->removeWidget(start_widget);
    this->setWindowTitle(QString("New Game"));

    delete start_widget;
}

void MainMenu::newGameBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(newgame_widget);
    this->setWindowTitle(QString("Main Menu"));

   delete newgame_widget;
}

void MainMenu::options()
{
    options_widget = new Options(profiles, this);
    main_layout->addWidget(options_widget);
    main_layout->removeWidget(start_widget);
    this->setWindowTitle(QString("Options"));

    delete start_widget;
}

void MainMenu::optionsBack()
{
    start_widget = new Start(this);
    main_layout->addWidget(start_widget);
    main_layout->removeWidget(options_widget);
    this->setWindowTitle(QString("Main Menu"));

    delete options_widget;
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
        for(int i = 0; i < profiles.size(); i++)
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
