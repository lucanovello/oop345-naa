#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>
#include <iostream>

namespace seneca
{
    class Guild
    {
        std::string m_guildName;
        Character** m_guildMembers{};
        size_t m_guildSize{ 0 };

    public:
        Guild();
        Guild(const char* name);
        Guild(const Guild& other);
        Guild& operator=(const Guild& other);
        Guild(Guild&& other) noexcept;
        Guild& operator=(Guild&& other) noexcept;
        ~Guild();

        void addMember(Character* c);
        void removeMember(const std::string& name);
        Character* operator[](size_t idx) const;
        void showMembers() const;

    private:
        void resize();
        void free();
    };
}

#endif
