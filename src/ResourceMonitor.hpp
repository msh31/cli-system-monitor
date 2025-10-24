#pragma once
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ResourceMonitor {
    public:
        void getJSONdata(std::string filePath);

    private:
        int CPU_THRESHOLD, CPU_MAXTEMP, RAM_THRESHOLD, PROCESS_THRESHOLD;
};
