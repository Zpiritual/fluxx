//Container for a player's name

#ifndef PROFILENAME_H
#define PROFILENAME_H

#include <string>

struct ProfileName
{
    std::string val;

    ProfileName(std::string val) : val{val}
    {}

    ProfileName() = default;
    ProfileName(const ProfileName&) = default;
    ProfileName (ProfileName&&) = default;

    ProfileName& operator=(const ProfileName&) = default;
    ProfileName& operator=(ProfileName&&) = default;

    ~ProfileName() = default;

    bool operator ==(const ProfileName& p) const
    {
        return val == p.val;
    }

    bool operator !=(const ProfileName& p) const
    {
        return !(*this == p);
    }

    bool operator <(const ProfileName& p) const
    {
        return val < p.val;
    }
};

#endif // PROFILENAME_H
