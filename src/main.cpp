#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include "ResourceMonitor.hpp"

using json = nlohmann::json;

int main() {
    std::cout << "hi\n";
    std::ifstream f("config.json");
    json data = json::parse(f);
    std::cout << data << "\n";
    return 0;
}
