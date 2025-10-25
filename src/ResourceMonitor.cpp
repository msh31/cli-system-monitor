#include "ResourceMonitor.hpp"
#include <chrono>
#include <string>
#include <sysinfoapi.h>

#define WIDTH 7
#define DIV 1048576 //the byte to megabyte conversion
#define CHECK_PDH_STATUS(s) if ((s) != ERROR_SUCCESS) return -1; //neat lil macro, i thought they were booleans at first

ResourceMonitor::ResourceMonitor() {
    logFile.open(logFilePath, std::ios::app);
}

ResourceMonitor::~ResourceMonitor() {
   	if (logFile.is_open()) {
		logFile.close();
	}
}

void ResourceMonitor::getJSONdata(std::string filePath) {
    std::ifstream f(filePath);

    if (!f.is_open()) {
        std::cerr << "Error: Could not open config.json\n";
        exit(1);
    }

    json data = json::parse(f);

    CPU_THRESHOLD = data["CPU_THRESHOLD"];
    RAM_THRESHOLD = data["RAM_THRESHOLD"];
    PROCESS_THRESHOLD = data["PROCESS_THRESHOLD"];

    std::cout << "CPU Threshold: " << CPU_THRESHOLD << "\n";
    std::cout << "RAM Threshold: " << RAM_THRESHOLD << "\n\n";
    std::cout << "Process Threshold: " << PROCESS_THRESHOLD << "\n\n";
}

/**
 * @brief Gets the CPU usage using the Performance Data Helper (PDH) API.
 *
 * @param waitTime The time to wait (in milliseconds) before calling PdhCollectQueryData() again.
 * @return The total percentage of CPU being used as an integer.
 */
float ResourceMonitor::getCpuUsage(int waitTime) {
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    PDH_FMT_COUNTERVALUE counterVal;

    CHECK_PDH_STATUS(PdhOpenQueryW(nullptr, 0, &query));

    CHECK_PDH_STATUS(PdhAddCounterW(query, L"\\Processor(_Total)\\% Processor Time", 0, &counter));

    CHECK_PDH_STATUS(PdhCollectQueryData(query));

    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

    CHECK_PDH_STATUS(PdhCollectQueryData(query));

    CHECK_PDH_STATUS(PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, nullptr, &counterVal));

    PdhCloseQuery(query);
    return counterVal.doubleValue;
}

int ResourceMonitor::getRamUsage() {
    memStatus.dwLength = sizeof(memStatus);
    GlobalMemoryStatusEx (&memStatus);

    // a bit inaccurate, but we dont care for now
    auto availablePhysicalMemory = memStatus.ullTotalPhys - memStatus.ullAvailPhys;

    // _tprintf (TEXT("There is  %*ld percent of memory in use.\n"),WIDTH, memStatus.dwMemoryLoad);
    // _tprintf (TEXT("There are %*I64d total Mbytes of physical memory.\n"),WIDTH,memStatus.ullTotalPhys/DIV);
    // _tprintf (TEXT("There are %*I64d free Mbytes of physical memory.\n"),WIDTH, memStatus.ullAvailPhys/DIV);
    // _tprintf (TEXT("There are %*I64d total Mbytes of paging file.\n"),WIDTH, memStatus.ullTotalPageFile/DIV);
    // _tprintf (TEXT("There are %*I64d free Mbytes of paging file.\n"),WIDTH, memStatus.ullAvailPageFile/DIV);
    // _tprintf (TEXT("There are %*I64d total Mbytes of virtual memory.\n"),WIDTH, memStatus.ullTotalVirtual/DIV);
    // _tprintf (TEXT("There are %*I64d free Mbytes of virtual memory.\n"),WIDTH, memStatus.ullAvailVirtual/DIV);
    // _tprintf (TEXT("There are %*I64d free Mbytes of extended memory.\n"),WIDTH, memStatus.ullAvailExtendedVirtual/DIV);

    // returns in Mb
    return availablePhysicalMemory/DIV;
}

int ResourceMonitor::getprocessCount() {
    DWORD processIDs[1024];
    DWORD bytesReturned;

    if (!EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned)) {
        return -1;
    }

    return bytesReturned / sizeof(DWORD);
}

void ResourceMonitor::logAlert(std::string text) {
    GetLocalTime(&sysTime);

    std::ostringstream oss;
    oss << "[" << sysTime.wHour << ":" << sysTime.wMinute << ":" << sysTime.wSecond << "] "
        << "ALERT: " << text;

    std::string logMessage = oss.str();
    std::cout << logMessage << "\n";

	if (!logFile.is_open()) {
		logFile.open(logFilePath, std::ios::app);

		if (!logFile.is_open()) {
			std::cerr << "Error: Could not open log file at " << logFilePath << ". Disabling file logging.\n";
			return;
		}
	}

	logFile << logMessage << "\n";
	logFile.flush();
}

void ResourceMonitor::runAnalysis() {
    //maybe not that good of a design, but whatever
    float cpuUsage = getCpuUsage(500);
    int ramUsage = getRamUsage(); //again, in mb like if you have 8GB, it'd be 8192 for example as per teh config.json
    int procCount = getprocessCount();

    if (cpuUsage > CPU_THRESHOLD) {
        logAlert("CPU usage at: " + std::to_string(cpuUsage) + "% (threshold: " + std::to_string(CPU_THRESHOLD) + "%)");
    }

    if (ramUsage > RAM_THRESHOLD) {
        logAlert("RAM usage at: " + std::to_string(ramUsage) + "MB (threshold: " + std::to_string(RAM_THRESHOLD) + "MB)");
    }

    if (procCount > PROCESS_THRESHOLD) {
        logAlert("Process count at: " + std::to_string(procCount) + " (threshold: " + std::to_string(PROCESS_THRESHOLD) + ")");
    }
}
