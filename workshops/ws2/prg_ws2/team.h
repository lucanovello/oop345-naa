#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>
#include <iostream>

namespace seneca
{
    class Team
    {
        std::string m_teamName;
        Character** m_teamMembers{};
        size_t m_teamSize{ 0 };

    public:
        Team();
        Team(const char* name);
        Team(const Team& other);
        Team& operator=(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;
        ~Team();

        void addMember(const Character* c);
        void removeMember(const std::string& name);
        Character* operator[](size_t idx) const;
        void showMembers() const;

    private:
        void resize();
        void free();
    };
}

#endif
