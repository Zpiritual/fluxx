//Track the the stats of profiles internally

#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "profilename.h"
#include "Player.h"

class Profile
{
public:
    Profile(const std::string& n = "tempName", int w = 0, int g = 0, int pc = 0, int dc = 0, int mcp = 0, int t = 0);
    ~Profile();

    Profile& operator+=(const PlayerStats&);

    void checkStat(std::istringstream& is, const std::string&);

    const std::string& getName() const;
    int getWins() const;
    int getGames() const;
    int getPlayedCards() const;
    int getDrawnCards() const;
    int getMaxConsecutivePlays() const;
    int getPlayTime() const;

    void setName(const std::string&);
    void setWins(int);
    void setGames(int);
    void setPlayedCards(int);
    void setDrawnCards(int);
    void setMaxConsecutivePlays(int);
    void setPlayTime(int);
    void readLine(const std::string&);

private:
    ProfileName name;
    int wins;
    int games;
    int played_cards;
    int drawn_cards;
    int max_consecutive_plays;
    int play_time;
};

std::ostream& operator<<(std::ostream&, const Profile&);
std::istream& operator>>(std::istream&, Profile&);

#endif // PROFILE_H
