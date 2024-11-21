#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <array>
#include <ostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace seneca {

    class SpellChecker {
        static constexpr size_t WORD_COUNT = 6;
        std::array<std::string, WORD_COUNT> m_badWords{};
        std::array<std::string, WORD_COUNT> m_goodWords{};
        std::array<size_t, WORD_COUNT> m_replacements{};
    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };

} // namespace seneca

#endif // SENECA_SPELLCHECKER_H
