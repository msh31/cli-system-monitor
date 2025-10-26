#pragma once
#include <exception>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <memory>
#include <vector>

#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <pdh.h> // performance data helper
#include <pdhmsg.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ResourceMonitor {
    public:
        ResourceMonitor();
        ~ResourceMonitor();

        void getJSONdata(std::string filePath);
        void runAnalysis();
        void readHistory();

        float getCpuUsage(int waitTime);
        int getRamUsage();
        int getprocessCount();

    private:
        int CPU_MAXTEMP, RAM_THRESHOLD, PROCESS_THRESHOLD;
        float CPU_THRESHOLD;
        MEMORYSTATUSEX memStatus;
        SYSTEMTIME sysTime;

        std::ofstream logFile;
        std::string logFilePath = "alerts.log";

        std::vector<float> cpuHistory;
        std::vector<int> ramHistory;
        std::vector<int> procHistory;

        void logAlert(std::string text);
};

class ExceptionHandler : public std::exception {
    private:
        std::string _message;

    public:
        ExceptionHandler(const std::string& message) {
            _message = message;
        }

        const char* what() const override {
            return _message.c_str();
        }
};
