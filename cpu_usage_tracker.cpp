#include "cpu_usage_tracker.hpp"

/**
 * @brief Ensuree the thread is stopped when the object is destroyed
 */
CpuUsageTracker::~CpuUsageTracker() {
    stopReadingThread();
}

/**
 * @brief Retrieves the only availabile instance of the CpuUsageTracker class
 * @param cpuUsageGraph CpuUsageGraph object that is used to draw the current cpu usage
 * @return The instance of CpuUsageTracker
 */
CpuUsageTracker& CpuUsageTracker::getInstance(CpuUsageGraph *cpuUsageGraph) {
    static CpuUsageTracker instance(cpuUsageGraph);
    return instance;
}

/**
 * @return the cpuUsageHistory deque which saves all the measuring data of the cpu usage
 */
/*std::deque<double> CpuUsageTracker::getCpuUsageHistory() {
    std::lock_guard<std::mutex> lock(dataMutex);
    return cpuUsageHistory;
}*/


ULONGLONG CpuUsageTracker::ToUInt64(const FILETIME& ft) {
    return ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
}

/**
 * @brief calculates CPU usage percentage based on how much time the CPU spent idle vs working, between two moments in time
 * @return the percentage value (double) of cpu usage
 */
double CpuUsageTracker::getCurrentCpuUsage() {
    FILETIME idleTime, kernelTime, userTime;

    // Gets the cpu times saving the following parameters:
    //  - idleTime: how long the system has been idle
    //  - kernelTime: time spent in kernel mode (includes idle time)
    //  - userTime: time spent in user mode
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        static FILETIME lastIdleTime = {0, 0};
        static FILETIME lastKernelTime = {0, 0};
        static FILETIME lastUserTime = {0, 0};

        // Calculating the difference from last update
        ULONGLONG idleDiff = ToUInt64(idleTime) - ToUInt64(lastIdleTime);
        ULONGLONG kernelDiff = ToUInt64(kernelTime) - ToUInt64(lastKernelTime);
        ULONGLONG userDiff = ToUInt64(userTime) - ToUInt64(lastUserTime);

        // Update previous for next measurement
        lastIdleTime = idleTime;
        lastKernelTime = kernelTime;
        lastUserTime = userTime;

        // Computing the cpu usage
        ULONGLONG systemDiff = (kernelDiff + userDiff) - idleDiff;
        ULONGLONG totalDiff = kernelDiff + userDiff;

        return (totalDiff == 0) ? 0.0 : 100.0 * ((double)systemDiff / (double)totalDiff);
    }

    return 0.0;
}

void CpuUsageTracker::updateReading() {
    double cpuUsage = getCurrentCpuUsage();

    if (graph) {
        graph->updateChart(cpuUsage);
    }
}


void CpuUsageTracker::startReadingThread() {
    stopThreadFlag = false;
    readingThread = std::thread([this]() {
        while (!stopThreadFlag) {
            CpuUsageTracker::updateReading();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });
}

void CpuUsageTracker::stopReadingThread() {
    if (readingThread.joinable()) {
        stopThreadFlag = true;
        readingThread.join();
    }
}







