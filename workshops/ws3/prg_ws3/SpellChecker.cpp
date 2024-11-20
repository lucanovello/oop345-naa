#include "SpellChecker.h"

namespace seneca {

    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            throw "Bad file name!";
        }
        std::string line;
        size_t index = 0;
        while (std::getline(file, line) && index < WORD_COUNT) {
            std::istringstream stream(line);
            stream >> m_badWords[index] >> m_goodWords[index];
            ++index;
        }
        if (index != WORD_COUNT) {
            throw "File does not contain enough word pairs!";
        }
    }

    void SpellChecker::operator()(std::string& text) {
        for (size_t i = 0; i < WORD_COUNT; ++i) {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacements[i]++;
                pos += m_goodWords[i].length();
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const {
        for (size_t i = 0; i < WORD_COUNT; ++i) {
            out << std::right << std::setw(15) << m_badWords[i] << ": "
                << m_replacements[i] << " replacements" << std::endl;
        }
    }

} // namespace seneca
