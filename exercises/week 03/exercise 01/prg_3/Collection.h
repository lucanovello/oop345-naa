#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>

template <typename T, size_t CAPACITY>
class Collection
{
	T m_collection[CAPACITY]{};
	size_t m_size{};
	static T m_defaultValue;
public:
	size_t size() const { return m_size; }
	std::ostream& display(std::ostream& os) const
	{
		for (size_t i = 0; i < m_size; i++)
		{
			os << m_collection[i] << std::endl;
		}
		return os;
	}	
	virtual bool add(const T& item)
	{
		if (m_size < CAPACITY)
		{
			m_collection[m_size] = item;
			m_size++;
			return true;
		}
		else
		{
			return false;
		}
	}


};




#endif // !SENECA_COLLECTION_H

