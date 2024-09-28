#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H
#include <string>

namespace seneca
{
	class ProteinDatabase
	{
		std::string* proteinUIDs{ nullptr };
		std::string* aminoAcidSequences{ nullptr };
		size_t noOfProteins{};
	public:
		ProteinDatabase();
		ProteinDatabase(const std::string& filename);
		ProteinDatabase(const ProteinDatabase& src);
		ProteinDatabase(const ProteinDatabase&& src) noexcept;
		ProteinDatabase& operator=(const ProteinDatabase& src);
		ProteinDatabase& operator=(ProteinDatabase&& src) noexcept;
		~ProteinDatabase();
		size_t size();
		std::string operator[](size_t) const;
		std::string getUID(size_t) const;

	}; // !class ProteinDatabase
} // !namespace seneca
#endif // !SENECA_PROTEINDATABASE_H