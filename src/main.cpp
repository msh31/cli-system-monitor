#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <csignal>
#include <vector>

#include "ResourceMonitor.hpp"

#define LOOP_INTERVAL 2

ResourceMonitor resMon;
int timeRan = 0;
std::vector<std::string> browsersToCheck = { //non existing ones will just return 0
    "chrome.exe",
    "firefox.exe",
    "msedge.exe",
    "brave.exe",
    "vivaldi.exe",
    "waterfox.exe",
    "librewolf.exe",
    "opera.exe"
};

void signalHandler(int signal) {
    resMon.readHistory(); // last 10 readings
    std::cout << "Time (in seconds) the program has ran: " << timeRan << "\n";
    std::cout << "Alerts can be found in: alerts.log! (timestamped)\n";
    exit(signal);
}

std::string stripExtension(const std::string& name) {
    size_t dot = name.rfind(".");

    if (dot == std::string::npos) {
        return name;
    }

    return name.substr(0, dot);
}

int main() {
    signal(SIGINT, signalHandler);

    try {
        resMon.getJSONdata("config.json");
    }
    catch (const ExceptionHandler& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    // for (const auto& browser : browsersToCheck) {
    //     std::cout << stripExtension(browser) << "'s ram usage: 0MB\n";
    // }

    bool firstRun = true;
    while (true) {
        //TODO: improve CPU & RAM precision
        resMon.runAnalysis();

        // move cursor up N lines
        if (!firstRun) {
            std::cout << "\033[" << browsersToCheck.size() << "A";
        }
        firstRun = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        for (const auto& browser : browsersToCheck) {
            size_t memory = 0;

            try {
                memory = resMon.getProcessRamUsage(browser);
            }
            catch (const ExceptionHandler& ex) {
                std::cerr << "Error: " << ex.what() << "\n";
            }

            std::string display = stripExtension(browser);

            // clear line, overwrite without adding new line
            std::cout << "\33[2K\r" << display << " :" << memory << "MB\n" << std::flush;
        }

        std::this_thread::sleep_for(std::chrono::seconds(LOOP_INTERVAL));
        timeRan++;
    }

    return 0;
}
