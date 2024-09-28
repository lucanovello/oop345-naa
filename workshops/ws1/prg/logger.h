#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
#include <iostream>

namespace seneca {
    class Logger {
        Event* m_events = nullptr;
        size_t m_size = 0;
        size_t m_capacity = 1;
    public:
        Logger();
        ~Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&& other) noexcept;
        Logger& operator=(Logger&& other) noexcept;
        void addEvent(const Event& event);
        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };
}
#endif // SENECA_LOGGER_H
