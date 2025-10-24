#pragma once
#include <iostream>
#include <fstream>

#include <windows.h>
#include <psapi.h>
#include <tchar.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ResourceMonitor {
    public:
        void getJSONdata(std::string filePath);
        int getCpuUsage();
        int getRamUsage();
        int getprocessCount();

    private:
        int CPU_THRESHOLD, CPU_MAXTEMP, RAM_THRESHOLD, PROCESS_THRESHOLD;
        MEMORYSTATUSEX memStatus;
};
