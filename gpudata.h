#pragma once
#include "amd_ags.h"
#include <stdlib.h>
#include <iostream>
#pragma comment(lib,"amd_ags_x64.lib")
AGSGPUInfo gpuInfo;
uint64_t gpuIndex = 0;
AGSContext *context;
AGSReturnCode code = agsInitialize(AGS_CURRENT_VERSION, nullptr, &context, &gpuInfo);
const AGSDeviceInfo AGSInfo = gpuInfo.devices[gpuIndex];
class GPU_DATA {
public:
    uint64_t GPUlocalMemory = AGSInfo.localMemoryInBytes;
    uint64_t GPUSharedMemory = AGSInfo.sharedMemoryInBytes;
    uint64_t GPUCoreClock = AGSInfo.coreClock;//
    uint64_t GPUMemoryClock = AGSInfo.memoryClock;
    uint64_t GPUNumberCUs = AGSInfo.numCUs;
    uint64_t GPUNumberROPs = AGSInfo.numROPs;
    uint64_t GPUNumberWGPs = AGSInfo.numWGPs;
    uint64_t GPUMemoryBandwidth = AGSInfo.memoryBandwidth;
  };


GPU_DATA* AGPU = new GPU_DATA;///
