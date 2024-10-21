#include "team.h"
#include <cstring>

namespace seneca
{
	Team::Team() : m_teamName("No team") {}

	Team::Team(const char* name) : m_teamName(name) {}

	Team::Team(const Team& other) : m_teamName(other.m_teamName), m_teamSize(other.m_teamSize)
	{
		m_teamMembers = new Character * [m_teamSize];
		for (size_t i = 0; i < m_teamSize; ++i)
		{
			m_teamMembers[i] = other.m_teamMembers[i]->clone();
		}
	}

	Team& Team::operator=(const Team& other)
	{
		if (this != &other)
		{
			free();
			m_teamName = other.m_teamName;
			m_teamSize = other.m_teamSize;
			m_teamMembers = new Character * [m_teamSize];
			for (size_t i = 0; i < m_teamSize; ++i)
			{
				m_teamMembers[i] = other.m_teamMembers[i]->clone();
			}
		}
		return *this;
	}

	Team::Team(Team&& other) noexcept : m_teamName(std::move(other.m_teamName)), m_teamMembers(other.m_teamMembers), m_teamSize(other.m_teamSize)
	{
		other.m_teamMembers = nullptr;
		other.m_teamSize = 0;
	}

	Team& Team::operator=(Team&& other) noexcept
	{
		if (this != &other)
		{
			free();
			m_teamName = std::move(other.m_teamName);
			m_teamMembers = other.m_teamMembers;
			m_teamSize = other.m_teamSize;
			other.m_teamMembers = nullptr;
			other.m_teamSize = 0;
		}
		return *this;
	}

	Team::~Team()
	{
		delete[] m_teamMembers;
	}

	void Team::addMember(const Character* c) {
		if (c == nullptr) return;

		for (size_t i = 0; i < m_teamSize; ++i) {
			if (m_teamMembers[i] && m_teamMembers[i]->getName() == c->getName()) {
				return;
			}
		}

		Character* newMember = c->clone();
		Character** newArray = new Character * [m_teamSize + 1];

		for (size_t i = 0; i < m_teamSize; ++i) {
			newArray[i] = m_teamMembers[i];
		}

		newArray[m_teamSize] = newMember;
		delete[] m_teamMembers;
		m_teamMembers = newArray;
		m_teamSize++;
	}


	void Team::removeMember(const std::string& name) {
		for (size_t i = 0; i < m_teamSize; ++i) {
			if (m_teamMembers[i]->getName() == name) {
				delete m_teamMembers[i];
				for (size_t j = i; j < m_teamSize - 1; ++j) {
					m_teamMembers[j] = m_teamMembers[j + 1];
				}
				m_teamMembers[m_teamSize - 1] = nullptr;
				m_teamSize--;
				return;
			}
		}
	}


	Character* Team::operator[](size_t idx) const
	{
		return (idx < m_teamSize) ? m_teamMembers[idx] : nullptr;
	}

	void Team::showMembers() const
	{
		if (m_teamSize == 0)
		{
			std::cout << "No team.\n";
		}
		else
		{
			std::cout << "[Team] " << m_teamName << "\n";
			for (size_t i = 0; i < m_teamSize; ++i)
			{
				std::cout << "    " << (i + 1) << ": " << *m_teamMembers[i] << "\n";
			}
		}
	}

	void Team::resize()
	{
		Character** temp = new Character * [m_teamSize + 1];
		for (size_t i = 0; i < m_teamSize; ++i)
		{
			temp[i] = m_teamMembers[i];
		}
		delete[] m_teamMembers;
		m_teamMembers = temp;
		++m_teamSize;
	}

	void Team::free() {
		for (size_t i = 0; i < m_teamSize; ++i)
		{
			delete m_teamMembers[i];
		}
		delete[] m_teamMembers;
		m_teamMembers = nullptr;
		m_teamSize = 0;
	}

}
