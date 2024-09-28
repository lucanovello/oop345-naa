#include "logger.h"

namespace seneca {
    Logger::Logger() {
        m_events = new Event[m_capacity];
    }

    Logger::~Logger() {
        delete[] m_events;
    }

    Logger::Logger(Logger&& other) noexcept
        : m_events(other.m_events), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.m_events = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Logger& Logger::operator=(Logger&& other) noexcept {
        if (this != &other) {
            delete[] m_events;
            m_events = other.m_events;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_events = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    void Logger::addEvent(const Event& event) {
        if (m_size >= m_capacity) {
            m_capacity *= 2;
            Event* temp = new Event[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                temp[i] = std::move(m_events[i]);
            }
            delete[] m_events;
            m_events = temp;
        }
        m_events[m_size++] = event;
    }

    std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.m_size; ++i) {
            os << logger.m_events[i] << std::endl;
        }
        return os;
    }
}