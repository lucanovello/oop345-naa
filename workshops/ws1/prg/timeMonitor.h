/////////////////////////////
//  Luca Novello
//  038515003
//  gnovello@myseneca.ca
//  Sept 24 2024
/////////////////////////////

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include "event.h"
#include <chrono>

namespace seneca {
    class TimeMonitor {
        const char* m_eventName = nullptr;
        std::chrono::high_resolution_clock::time_point m_start;
    public:
        TimeMonitor() = default;
        void startEvent(const char* name);
        Event stopEvent();
    };
}
#endif // SENECA_TIMEMONITOR_H