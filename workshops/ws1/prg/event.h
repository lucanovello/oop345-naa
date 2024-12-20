/////////////////////////////
//  Luca Novello
//  038515003
//  gnovello@myseneca.ca
//  Sept 24 2024
/////////////////////////////
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "settings.h"

namespace seneca {
    class Event {
        std::string m_name;
        std::chrono::nanoseconds m_duration;
    public:
        Event() = default;
        Event(const char* name, const std::chrono::nanoseconds& duration);
        friend std::ostream& operator<<(std::ostream& os, const Event& event);
    };
}
#endif // SENECA_EVENT_H
