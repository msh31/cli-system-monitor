#include <iostream>

#include "ResourceMonitor.hpp"

int main() {
    ResourceMonitor resMon;
    resMon.getJSONdata("config.json");

    return 0;
}
