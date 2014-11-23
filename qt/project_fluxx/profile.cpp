#include "profile.h"

Profile::Profile()
    : name(std::string{"tempName"})
{
    wins = 0;
    games = 0;
    played_cards = 0;
}

Profile::Profile(const std::string& n, int win, int game, int cards)
    : name(n)
{
    wins = win;
    games = game;
    played_cards = cards;
}

Profile::~Profile()
{

}

Profile& Profile::operator=(const Player& player)
{
    //name = player.getID();

    return *this;
}

const std::string& Profile::getName() const
{
    return name.val;
}

int Profile::getWins() const
{
    return wins;
}

int Profile::getGames() const
{
    return games;
}

int Profile::getPlayedCards() const
{
    return played_cards;
}

void Profile::setName(const std::string& s)
{
    name.val = s;
}

void Profile::setWins(int w)
{
    wins = w;
}

void Profile::setGames(int g)
{
    games = g;
}

void Profile::setPlayedCards(int pg)
{
    played_cards = pg;
}

void Profile::checkStat(std::istringstream& is, const std::string& stat)
{
    if(stat == "profile")
    {
        std::string n;
        is >> n;
        name.val = n;
    }
    else if(stat == "games")
    {
        int g;
        is >> g;
        games = g;
    }
    else if(stat == "wins")
    {
        int w;
        is >> w;
        wins = w;
    }
    else if(stat == "playedcards")
    {
        int pc;
        is >> pc;
        played_cards = pc;
    }
}

std::ostream& operator<<(std::ostream& os, const Profile& profile)
{
    os << "profile " << profile.getName() << "\n"
       << "wins " << profile.getWins() << "\n"
       << "games " << profile.getGames() << "\n"
       << "playedcards " << profile.getPlayedCards() << "\n\n";
    return os;
}


std::istream& operator>>(std::istream& is, Profile& profile)
{
    std::string stat;
    std::string line;

    getline(is, line);
    while(line != "")
    {
        std::istringstream iss(line);
        iss >> stat;
        std::transform(stat.begin(), stat.end(), stat.begin(), ::tolower);
        profile.checkStat(iss, stat);
        getline(is, line);
    }

    return is;
}
