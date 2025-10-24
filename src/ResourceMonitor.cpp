#include "ResourceMonitor.hpp"
#include <windows.h>
#include <psapi.h>

void ResourceMonitor::getJSONdata(std::string filePath) {
    std::ifstream f(filePath);

    if (!f.is_open()) {
        std::cerr << "Error: Could not open config.json\n";
        exit(1);
    }

    json data = json::parse(f);

    CPU_THRESHOLD = data["CPU_THRESHOLD"];
    CPU_MAXTEMP = data["CPU_MAXTEMP"];
    RAM_THRESHOLD = data["RAM_THRESHOLD"];
    PROCESS_THRESHOLD = data["PROCESS_THRESHOLD"];

    std::cout << "CPU Threshold: " << CPU_THRESHOLD << "\n";
    std::cout << "CPU Max temp: " << CPU_MAXTEMP << "\n\n";
    std::cout << "RAM Threshold: " << RAM_THRESHOLD << "\n\n";
    std::cout << "Process Threshold: " << PROCESS_THRESHOLD << "\n";
}

int ResourceMonitor::getCpuUsage() {
    //TODO
    return 0;
}

int ResourceMonitor::getRamUsage() {
    //TODO
    return 0;
}

int ResourceMonitor::getprocessCount() {
    DWORD processIDs[1024];
    DWORD bytesReturned;

    if (!EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned)) {
        return -1;
    }

    return bytesReturned / sizeof(DWORD);
}
