#include <iostream>

#include "ResourceMonitor.hpp"

#define LOOP_INTERVAL 1

int main() {
    ResourceMonitor resMon;
    resMon.getJSONdata("config.json");

    while (true) {
        //TODO: improve CPU & RAM precision
        resMon.runAnalysis();

        std::this_thread::sleep_for(std::chrono::seconds(LOOP_INTERVAL));
    }

    return 0;
}
