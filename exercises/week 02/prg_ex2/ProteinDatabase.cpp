#include "ProteinDatabase.h"
#include <iostream>
#include <string>
#include <fstream>

namespace seneca
{
	ProteinDatabase::ProteinDatabase()
	{
		std::string* proteinUIDs = nullptr;
		std::string* aminoAcidSequences = nullptr;
		size_t noOfProteins = 0;
	}

	ProteinDatabase::ProteinDatabase(const std::string& filename)
	{
		std::ifstream f(filename.c_str());
		noOfProteins = 0;
		aminoAcidSequences = nullptr;
		if (!f)
			return;

		std::string line, uid, name;
		// count the number of protein sequences
		while (std::getline(f, line).good())
		{
			if (line[0] == '>') { // start of a new protein
				noOfProteins++;
			}
		}

		f.clear();
		f.seekg(std::ios::beg);
		proteinUIDs = new std::string[noOfProteins];
		aminoAcidSequences = new std::string[noOfProteins];
		line.clear();
		int i = -1;
		while (std::getline(f, line).good())
		{
			if (line[0] == '>') { // start of a new of protein
				++i;

				name = line.substr(1);

				// extract the Unique ID
				// the Unique ID starts at index 4 and lasts until the first '|' after that
				proteinUIDs[i] = line.substr(4u, line.find_first_of('|', 4u) - 4u);
			}
			else
			{
				aminoAcidSequences[i] += line;
			}
		}
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& src)
	{
		*this = src;
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src)
	{
		if (this != &src) {
			delete[] proteinUIDs;
			proteinUIDs = nullptr;
			delete[] aminoAcidSequences;
			aminoAcidSequences = nullptr;

			noOfProteins = src.noOfProteins;

			if (noOfProteins != 0)
			{
				proteinUIDs = new std::string[noOfProteins];
				aminoAcidSequences = new std::string[noOfProteins];
				for (size_t i = 0; i < src.noOfProteins; i++) {
					proteinUIDs[i] = src.proteinUIDs[i];
					aminoAcidSequences[i] = src.aminoAcidSequences[i];
				}
			}
		}
		return *this;
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase&& src) noexcept
	{
		*this = std::move(src);
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src) noexcept
	{
		if (this != &src) {
			noOfProteins = src.noOfProteins;
			delete[] proteinUIDs;
			delete[] aminoAcidSequences;
			proteinUIDs = src.proteinUIDs;
			aminoAcidSequences = src.aminoAcidSequences;
			src.noOfProteins = 0;
			src.proteinUIDs = nullptr;
			src.aminoAcidSequences = nullptr;
		}
		return *this;
	}

	ProteinDatabase::~ProteinDatabase()
	{
		delete[] proteinUIDs;
		delete[] aminoAcidSequences;
	}

	size_t ProteinDatabase::size()
	{
		return noOfProteins;
	}

	std::string ProteinDatabase::operator[](size_t index) const
	{
		std::string result;
		if (index < noOfProteins)
		{
			result = aminoAcidSequences[index];
		}
		else {
			result = "";
		}
		return result;
	}

	std::string ProteinDatabase::getUID(size_t index) const
	{
		std::string result;
		if (index < noOfProteins)
		{
			result = proteinUIDs[index];
		}
		else {
			result = "";
		}
		return result;
	}
}
