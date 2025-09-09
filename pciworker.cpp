#include "pciworker.h"

PciWorker::PciWorker(const std::string& path) : path{path} {
    std::ifstream file(path);
    std::string line;
    std::getline(file, line);
    std::regex pattern(R"(Bus\s+(\d+),\s*Device\s+(\d+),\s*Func\s+(\d+)\s*->\s*VendorID:\s*(0x[0-9a-fA-F]+),\s*DeviceID:\s*(0x[0-9a-fA-F]+))");
    std::smatch matches;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (std::regex_search(line, matches, pattern)) {
            PciWorker::PciDevice dev{};
            dev.bus = std::stoi(matches[1].str());
            dev.device = std::stoi(matches[2].str());
            dev.func = std::stoi(matches[3].str());
            dev.vendorId = matches[4].str();
            dev.deviceId = matches[5].str();
            devices.push_back(dev);
        }
    }
}

std::vector<PciWorker::PciDevice> PciWorker::getDevices() {
    return this->devices;
}
