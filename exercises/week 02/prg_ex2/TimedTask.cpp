#define _CRT_SECURE_NO_WARNINGS
#include "TimedTask.h"
#include <iostream>
#include <chrono>
#include <cstring>
#include <iomanip>

namespace seneca
{
	void TimedTask::startClock()
	{
		m_startTime = std::chrono::steady_clock::now();
	}

	void TimedTask::stopClock()
	{
		m_endTime = std::chrono::steady_clock::now();
	}

	void TimedTask::addTask(const char* name)
	{
		if (m_noOfRecords < MAX_TASKARRAY_SIZE) {
			std::strncpy(m_tasksArr[m_noOfRecords].taskName, name, MAX_TASKNAME_SIZE);
			m_tasksArr[m_noOfRecords].taskName[MAX_TASKNAME_SIZE] = '\0';
			std::strncpy(m_tasksArr[m_noOfRecords].timeUnit, "nanoseconds", MAX_TIMEUNIT_SIZE);
			m_tasksArr[m_noOfRecords].timeUnit[MAX_TIMEUNIT_SIZE] = '\0';
			m_tasksArr[m_noOfRecords].taskDuration = m_endTime - m_startTime;
			m_noOfRecords++;
		}
	}

	std::ostream& operator<<(std::ostream& os, TimedTask& timeTask)
	{
		if (os) {
			os << "Execution Times:\n";
			os << "--------------------------\n";
			for (size_t i = 0; i < timeTask.m_noOfRecords; i++)
			{
				os << std::left << std::setw(21) << timeTask.m_tasksArr[i].taskName;
				os << std::right << std::setw(13) << timeTask.m_tasksArr[i].taskDuration.count() << std::endl;
			}
		}
		return os;
	}
} // namespace seneca