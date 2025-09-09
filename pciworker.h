#ifndef PCIWORKER_H
#define PCIWORKER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

class PciWorker
{
public:
    struct PciDevice {
        int bus;
        int device;
        int func;
        std::string vendorId;
        std::string deviceId;
    };

    PciWorker(const std::string& path);

    std::vector<PciDevice> getDevices();

private:
    std::string path;
    std::vector<PciDevice> devices;
};

#endif // PCIWORKER_H
