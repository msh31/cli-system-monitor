#include <iostream>
#include <chrono>
#include <thread>

#include "ResourceMonitor.hpp"

#define LOOP_INTERVAL 1

int main() {
    ResourceMonitor resMon;
    resMon.getJSONdata("config.json");

    while (true) {
        std::cout << "Process Count: " << resMon.getprocessCount() << "\n";

        std::cout << "RAM Usage: " << resMon.getRamUsage() << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(LOOP_INTERVAL));
    }

    return 0;
}
