#include "guild.h"
#include <cstring>

namespace seneca
{
    Guild::Guild() : m_guildName("No guild") {}

    Guild::Guild(const char* name) : m_guildName(name) {}

    Guild::Guild(const Guild& other) : m_guildName(other.m_guildName), m_guildSize(other.m_guildSize)
    {
        m_guildMembers = new Character * [m_guildSize];
        for (size_t i = 0; i < m_guildSize; ++i)
        {
            m_guildMembers[i] = other.m_guildMembers[i]->clone();
        }
    }

    Guild& Guild::operator=(const Guild& other)
    {
        if (this != &other)
        {
            free();
            m_guildName = other.m_guildName;
            m_guildSize = other.m_guildSize;
            m_guildMembers = new Character * [m_guildSize];
            for (size_t i = 0; i < m_guildSize; ++i)
            {
                m_guildMembers[i] = other.m_guildMembers[i]->clone();
            }
        }
        return *this;
    }

    Guild::Guild(Guild&& other) noexcept : m_guildName(std::move(other.m_guildName)), m_guildMembers(other.m_guildMembers), m_guildSize(other.m_guildSize)
    {
        other.m_guildMembers = nullptr;
        other.m_guildSize = 0;
    }

    Guild& Guild::operator=(Guild&& other) noexcept
    {
        if (this != &other)
        {
            free();
            m_guildName = std::move(other.m_guildName);
            m_guildMembers = other.m_guildMembers;
            m_guildSize = other.m_guildSize;
            other.m_guildMembers = nullptr;
            other.m_guildSize = 0;
        }
        return *this;
    }

    Guild::~Guild()
    {
        delete[] m_guildMembers;
    }

    void Guild::addMember(Character* c)
    {
        for (size_t i = 0; i < m_guildSize; ++i)
        {
            if (m_guildMembers[i]->getName() == c->getName())
                return;
        }

        resize();
        c->setHealthMax(c->getHealthMax() + 300);
        m_guildMembers[m_guildSize - 1] = c;
    }

    void Guild::removeMember(const std::string& name)
    {
        for (size_t i = 0; i < m_guildSize; ++i)
        {
            if (m_guildMembers[i]->getName() == name)
            {
                m_guildMembers[i]->setHealthMax(m_guildMembers[i]->getHealthMax() - 300);
                return;
            }
        }
    }

    Character* Guild::operator[](size_t idx) const
    {
        return (idx < m_guildSize) ? m_guildMembers[idx] : nullptr;
    }

    void Guild::showMembers() const
    {
        if (m_guildSize == 0)
        {
            std::cout << "No guild.\n";
        }
        else
        {
            std::cout << "[Guild] " << m_guildName << "\n";
            for (size_t i = 0; i < m_guildSize; ++i)
            {
                std::cout << "    " << (i + 1) << ": " << *m_guildMembers[i] << "\n";
            }
        }
    }

    void Guild::resize()
    {
        Character** temp = new Character * [m_guildSize + 1];
        for (size_t i = 0; i < m_guildSize; ++i)
        {
            temp[i] = m_guildMembers[i];
        }
        delete[] m_guildMembers;
        m_guildMembers = temp;
        ++m_guildSize;
    }

    void Guild::free()
    {
        for (size_t i = 0; i < m_guildSize; ++i)
        {
            delete m_guildMembers[i];
        }
        delete[] m_guildMembers;
        m_guildMembers = nullptr;
        m_guildSize = 0;
    }
}
