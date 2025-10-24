#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <pdh.h> // performance data helper
#include <pdhmsg.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ResourceMonitor {
    public:
        void getJSONdata(std::string filePath);
        void runAnalysis();

        float getCpuUsage(int waitTime);
        int getRamUsage();
        int getprocessCount();

    private:
        int CPU_THRESHOLD, CPU_MAXTEMP, RAM_THRESHOLD, PROCESS_THRESHOLD;
        MEMORYSTATUSEX memStatus;
        SYSTEMTIME sysTime;

        void logToConsole(std::string text);
};
