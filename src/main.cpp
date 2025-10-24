#include <iostream>

#include "ResourceMonitor.hpp"

#define LOOP_INTERVAL 1

int main() {
    ResourceMonitor resMon;
    resMon.getJSONdata("config.json");

    while (true) {
        //TODO: improve CPU & RAM precision
        std::cout << "CPU Usage: " << resMon.getCpuUsage(500) << "\n";
        std::cout << "RAM Usage: " << resMon.getRamUsage() << "\n";
        std::cout << "Process Count: " << resMon.getprocessCount() << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(LOOP_INTERVAL));
    }

    return 0;
}
