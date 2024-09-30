#include "dictionary.h"
#include "settings.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace seneca {
    PartOfSpeech Dictionary::parsePartOfSpeech(const std::string& posString) const {
        if (posString == "n." || posString == "n. pl.") return PartOfSpeech::Noun;
        if (posString == "adv.") return PartOfSpeech::Adverb;
        if (posString == "a.") return PartOfSpeech::Adjective;
        if (posString == "v." || posString == "v. i." || posString == "v. t." || posString == "v. t. & i.") return PartOfSpeech::Verb;
        if (posString == "prep.") return PartOfSpeech::Preposition;
        if (posString == "pron.") return PartOfSpeech::Pronoun;
        if (posString == "conj.") return PartOfSpeech::Conjunction;
        if (posString == "interj.") return PartOfSpeech::Interjection;
        return PartOfSpeech::Unknown;
    }

	std::string convertPosToString(PartOfSpeech pos) {
		switch (pos) {
		case PartOfSpeech::Noun: return "noun";
		case PartOfSpeech::Adverb: return "adverb";
		case PartOfSpeech::Adjective: return "adjective";
		case PartOfSpeech::Verb: return "verb";
		case PartOfSpeech::Preposition: return "preposition";
		case PartOfSpeech::Pronoun: return "pronoun";
		case PartOfSpeech::Conjunction: return "conjunction";
		case PartOfSpeech::Interjection: return "interjection";
		default: return "";
		}
	}

    Dictionary::Dictionary(const char* filename) {
        if (filename == nullptr) {
            std::cerr << "Error: Null filename provided.\n";
            return;
        }
        loadFromFile(filename);
    }

    Dictionary::Dictionary(const Dictionary& other) {
        if (other.m_size > 0) {
            m_size = other.m_size;
            m_words = new Word[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_words[i] = other.m_words[i];
            }
        }
    }

    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            delete[] m_words;
            m_words = nullptr;
            m_size = 0;
            if (other.m_size > 0) {
                m_size = other.m_size;
                m_words = new Word[m_size];
                for (size_t i = 0; i < m_size; ++i) {
                    m_words[i] = other.m_words[i];
                }
            }
        }
        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept {
        m_words = other.m_words;
        m_size = other.m_size;
        other.m_words = nullptr;
        other.m_size = 0;
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] m_words;
            m_words = other.m_words;
            m_size = other.m_size;
            other.m_words = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    void Dictionary::loadFromFile(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            m_words = nullptr;
            m_size = 0;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            m_size++;
        }
        file.clear();
        file.seekg(0);
        m_words = new Word[m_size];
        size_t i = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string word, posString, definition;
            std::getline(iss, word, ',');
            std::getline(iss, posString, ',');
            std::getline(iss, definition, '\n');
            m_words[i].m_word = word;
            m_words[i].m_pos = convertPosToString(parsePartOfSpeech(posString));
            m_words[i].m_definition = definition;
            ++i;
        }
    }

    void Dictionary::searchWord(const char* word) const {
        bool found = false;
        for (size_t i = 0; i < m_size; ++i) {
            if (m_words[i].m_word == word) {
                if (!found) {
                    std::cout << m_words[i].m_word;
                    found = true;
                }
                else {
                    std::cout << std::string(m_words[i].m_word.size(), ' ');
                }
                if (g_settings.m_verbose && m_words[i].m_pos != "") {
                    std::cout << " - (" << m_words[i].m_pos << ") ";
                }
                else {
                    std::cout << " - ";
                }
                std::cout << m_words[i].m_definition << std::endl;
                if (!g_settings.m_show_all) break;
            }
        }
        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }
}
