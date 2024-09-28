#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <chrono>

namespace seneca
{
	const size_t MAX_TASKNAME_SIZE = 20;
	const size_t MAX_TIMEUNIT_SIZE = 12;
	const size_t MAX_TASKARRAY_SIZE = 10;
	class TimedTask
	{
		struct Task {
			char taskName[MAX_TASKNAME_SIZE + 1]{};
			char timeUnit[MAX_TIMEUNIT_SIZE + 1]{};
			std::chrono::steady_clock::duration taskDuration{};
		};
	public:
		Task m_tasksArr[MAX_TASKARRAY_SIZE]{};
		size_t m_noOfRecords{};
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_endTime;
		TimedTask() = default;
		void startClock();
		void stopClock();
		void addTask(const char* name);
		friend std::ostream& operator<<(std::ostream& os, TimedTask& timeTask);
	};
}
#endif // !SENECA_TIMEDTASK_H


