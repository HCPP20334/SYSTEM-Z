#pragma once
#include "amd_ags.h"
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <GL/GL.h>

#pragma comment(lib,"amd_ags_x64.lib")



AGSGPUInfo gpuInfo;
uint64_t gpuIndex = 0;
AGSContext* context;
AGSDeviceInfo AGSInfo;
uint64_t colorText(int64_t code) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)code);
    return 0;
}
std::string ConsolePutColored(std::string data, int64_t code) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)code);
    std::cout << data << std::endl;
    SetConsoleTextAttribute(hStdOut, (WORD)15);
    return "";
}

class GPU_DATA {
public:
    HWND hwnd = NULL;
   uint32_t GPUSMUnits = 0;
   uint32_t GPUTempOffset = 0;
   uint32_t GPULoadOffset = 0;
   //
   float GPUlocalMemory = 0;
   uint64_t GPUSharedMemory = 0;
   uint64_t GPUCoreClock = 0;
   uint64_t GPUMemoryClock = 0;
   uint64_t GPUNumberCUs = 0;
   uint64_t GPUNumberROPs = 0;
   uint64_t GPUNumberWGPs = 0;
   uint64_t GPUMemoryBandwidth = 0;
   uint64_t GPUTeraFlops = 0;
   std::string AGSInfoText; bool GPUNotAMD;
   std::string GPUInitMsg;
   int64_t SYSTEM_Z(std::string* outText);
   uint64_t wx = 600; uint64_t wy = 800;
   bool agsCheck();

  
};
int64_t GPU_DATA::SYSTEM_Z(std::string *outText) {
    static int64_t chrs = 0;
    static int64_t inDelay = 0;
    static bool bRevertText = 0;
    std::string fAText[] = { "S|       ","SY|       ","SYS|     ","SYST|      ","SYSTE|     ","SYSTEM|    ","SYSTEM-|   ","SYSTEM-Z   ","SYSTEM-Z 1.0" };
    inDelay++;
    if (inDelay >= 15) { if (!bRevertText) { chrs++; } else { chrs--; if (chrs <= 0) { bRevertText = false; } }inDelay = 0; }
    if (chrs > 7) { bRevertText = true; }
    *outText = (fAText[chrs]).c_str();
}
bool GPU_DATA::agsCheck() {
    AGSReturnCode code = agsInitialize(AGS_CURRENT_VERSION, nullptr, &context, &gpuInfo);
    if ((code) == AGS_FAILURE) {
        colorText(47);
        GPU_DATA::GPUInitMsg = "AGS::Init() -> Fatal Error!!";
        
    }
    if ((code) == AGS_SUCCESS) {
        colorText(37);
        GPU_DATA::GPUInitMsg = "Your GPU is AMD!!AGS::Init()->OK";
        colorText(15);
        AGSInfo = gpuInfo.devices[gpuIndex];
        GPU_DATA::GPUlocalMemory = AGSInfo.localMemoryInBytes;
        GPU_DATA::GPUSharedMemory = AGSInfo.sharedMemoryInBytes;
        GPU_DATA::GPUCoreClock = AGSInfo.coreClock;
        GPU_DATA::GPUMemoryClock = AGSInfo.memoryClock;
        GPU_DATA::GPUNumberCUs = AGSInfo.numCUs;
        GPU_DATA::GPUNumberROPs = AGSInfo.numROPs;
        GPU_DATA::GPUNumberWGPs = AGSInfo.numWGPs;
        GPU_DATA::GPUMemoryBandwidth = AGSInfo.memoryBandwidth / 1024.0f;
        GPU_DATA::GPUTeraFlops = AGSInfo.teraFlops;
       // GPU_DATA_FAKE::AGSInfoText = "AGS_SDK:OK";
        GPUNotAMD = true;
        return 0;
    }
}
uint64_t a = 0;
GPU_DATA* AGPU = new GPU_DATA;///


