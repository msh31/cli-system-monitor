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
    "vivaldi",
    "waterfox",
    "librefox",
    "opera"
};

void signalHandler(int signal) {
    resMon.readHistory(); // last 10 readings
    std::cout << "Time (in seconds) the program has ran: " << timeRan << "\n";
    exit(signal);
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

    while (true) {
        //TODO: improve CPU & RAM precision
        resMon.runAnalysis();

        for (const auto& browser : browsersToCheck) {
            size_t memory = resMon.getProcessRamUsage(browser);
            std::cout << browser << "'s ram usage: " << memory << "MB\n";
        }
        std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(LOOP_INTERVAL));
        timeRan++;
    }

    return 0;
}
