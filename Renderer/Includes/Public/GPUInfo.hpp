#pragma once
#include <string>

namespace mr {

struct GPUInfo {
    std::string name;
    uint32_t vendorId;
    uint32_t deviceId;

    uint64_t dedicatedVRAM;
    uint64_t sharedRam;
};

}
