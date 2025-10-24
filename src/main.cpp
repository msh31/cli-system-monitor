#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include "ResourceMonitor.hpp"

using json = nlohmann::json;

int main() {
    std::ifstream f("config.json");
    json data = json::parse(f);

    int CPU_THRESHOLD = data["CPU_THRESHOLD"];
    int CPU_MAXTEMP = data["CPU_MAXTEMP"];
    int RAM_THRESHOLD = data["RAM_THRESHOLD"];
    int PROCESS_THRESHOLD = data["PROCESS_THRESHOLD"];

    std::cout << "CPU Threshold: " << CPU_THRESHOLD << "\n";
    std::cout << "CPU Max temp: " << CPU_MAXTEMP << "\n\n";
    std::cout << "RAM Threshold: " << RAM_THRESHOLD << "\n\n";
    std::cout << "Process Threshold: " << PROCESS_THRESHOLD << "\n";

    return 0;
}
