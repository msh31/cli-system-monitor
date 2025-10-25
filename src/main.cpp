#include <iostream>

#include "ResourceMonitor.hpp"

#define LOOP_INTERVAL 2

int main() {
    ResourceMonitor resMon;
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

        std::this_thread::sleep_for(std::chrono::seconds(LOOP_INTERVAL));
    }

    return 0;
}
