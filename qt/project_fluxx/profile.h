#ifndef PROFILE_H
#define PROFILE_H

#include "PlayerID.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

class Profile
{
public:
    Profile();
    Profile(const std::string&, int, int, int);
    ~Profile();

    Profile& operator=(const Player&);

    void checkStat(std::istringstream& is, const std::string&);

    const std::string& getName() const;
    int getWins() const;
    int getGames() const;
    int getPlayedCards() const;

    void setName(const std::string&);
    void setWins(int);
    void setGames(int);
    void setPlayedCards(int);

private:
    PlayerID name;
    int wins;
    int games;
    int played_cards;


};

std::ostream& operator<<(std::ostream&, const Profile&);
std::istream& operator>>(std::istream&, Profile&);

#endif // PROFILE_H
