#ifndef CPU_USAGE_TRACKER_HPP
#define CPU_USAGE_TRACKER_HPP

#include <deque>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>

#include "windows.h"
#include "cpu_usage_graph.hpp"

class CpuUsageTracker {
public:

    // To ensure only one instance of the CpuUsageTracker class is created both the copy constructor and assignment operator are deleted
    CpuUsageTracker(const CpuUsageTracker&) = delete;
    CpuUsageTracker& operator=(const CpuUsageTracker&) = delete;

    static CpuUsageTracker& getInstance(CpuUsageGraph *cpuUsageGraph);

    void updateReading();

    ULONGLONG ToUInt64(const FILETIME& ft);

    void startReadingThread();
    void stopReadingThread();

private:
    CpuUsageGraph* graph = nullptr;

    CpuUsageTracker(CpuUsageGraph *cpuUsageGraph) {
        graph = cpuUsageGraph;
    }

    ~CpuUsageTracker();

    double getCurrentCpuUsage();

    std::mutex dataMutex;

    std::thread readingThread;
    std::atomic<bool> stopThreadFlag;
};
#endif // CPU_USAGE_TRACKER_HPP
