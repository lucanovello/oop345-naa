#include "timeMonitor.h"

namespace seneca {
    void TimeMonitor::startEvent(const char* name) {
        m_eventName = name;
        m_start = std::chrono::high_resolution_clock::now();
    }

    Event TimeMonitor::stopEvent() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_start);
        return Event(m_eventName, duration);
    }
}
