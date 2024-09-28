#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
#include <string>

namespace seneca {
    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };
    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };
    class Dictionary {
        Word* m_words{ nullptr };
        size_t m_size{ 0 };
    public:
        Dictionary() = default;
        Dictionary(const char* filename);
        Dictionary(const Dictionary& other);
        Dictionary& operator=(const Dictionary& other);
        Dictionary(Dictionary&& other) noexcept;
        Dictionary& operator=(Dictionary&& other) noexcept;
        ~Dictionary();
        void searchWord(const char* word) const;
    private:
        PartOfSpeech parsePartOfSpeech(const std::string& posString) const;
        void loadFromFile(const char* filename);
    };
}
#endif // SENECA_DICTIONARY_H
