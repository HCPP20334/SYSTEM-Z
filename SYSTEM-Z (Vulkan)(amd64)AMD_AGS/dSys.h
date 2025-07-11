//GetSySInfo Lib by HCPP 2023
#include <Psapi.h>
#include <windows.h>
#include <sysinfoapi.h>
#include <stdint.h>//-
#include <string>
int64_t ps_apiL(int64_t fps_count);
int64_t fPerfomanceInfo(int64_t fPdataId);
int64_t fMemStatus(int64_t fMData_0);
int64_t fLTime(int64_t fLtData);
int64_t CPUArch();
std::string fCPUType();
uint64_t CurrentWindowSizeW(HWND hwndW,uint64_t* wx, uint64_t* hy)
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = hwndW;
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    *wx = desktop.right;
    *hy = desktop.bottom;
    return 1;
}

/*
 * C++11 MinGW Compiler
 * for work add to Projects libpsapi.a & VS -> add #pragma comment(lib, "psapi.lib");
  func ps_apiL - send Faulting Pc and Faulting Va
  func fPerfomanceInfo return Perf Call Info
  func fMemStatus return call mem data's 
  func fLTTime sen Local Time
  func CPUArch send call cpu_bit's
  func fCPUType return cpu_type ('AMD x64','Intel x86')
 */
uint64_t fDataMemUsage() // Work Function !!! Check Sym RAM to Current Program //
{
	PROCESS_MEMORY_COUNTERS pmc;
	pmc.cb = sizeof(pmc);
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	return pmc.WorkingSetSize;
}

int64_t ps_apiL(int64_t fps_count)
{
	PSAPI_WS_WATCH_INFORMATION fPs_data;
	GetWsChanges(GetCurrentProcess(),&fPs_data,sizeof(fPs_data));
	if(!fps_count){
		fPs_data.FaultingPc;
	}
	if(fps_count){
		fPs_data.FaultingVa;
	}
}
int64_t fPerfomanceInfo(int64_t fPdataId)
{
    PERFORMANCE_INFORMATION	fPdata0A;
    fPdata0A.cb = sizeof(fPdata0A);
	GetPerformanceInfo(&fPdata0A,sizeof(fPdata0A));
	if(fPdataId == 1){
		return fPdata0A.CommitLimit;
	}
	if(fPdataId == 2){
		return fPdata0A.CommitPeak;
	}
	if(fPdataId == 3){
		return fPdata0A.CommitTotal;
	}
	if(fPdataId == 4){
		return fPdata0A.KernelNonpaged;
	}
	if(fPdataId == 5){
		return fPdata0A.KernelPaged;
	}
	if(fPdataId == 6){
		return fPdata0A.KernelTotal;
	}
	if(fPdataId == 7){
		return fPdata0A.PageSize;
	}
	if(fPdataId == 8){
		return (fPdata0A.PhysicalAvailable) / 1024;
	}
	if(fPdataId == 9){
		return fPdata0A.PhysicalTotal;
	}
	if(fPdataId == 10){
		return fPdata0A.ProcessCount;
	}
	if(fPdataId == 11){
		return fPdata0A.SystemCache;
	}
	if(fPdataId == 12){
		return fPdata0A.ThreadCount;
	}
}
int64_t fMemStatus(int64_t fMData_0)
{
	//MEMORYSTATUSEX fMemState_0A;
	MEMORYSTATUS fMemState_0A;

	// Zero structure
	memset(&fMemState_0A, 0, sizeof(fMemState_0A));

	// Get RAM snapshot
	::GlobalMemoryStatus(&fMemState_0A);
	if(fMData_0 == 0){
	return fMemState_0A.dwLength;
	}
	if(fMData_0 == 1){
	return (float)(fMemState_0A.dwMemoryLoad);
	}
	if(fMData_0 == 2){
	return fMemState_0A.dwAvailVirtual / 1024 / 1024 / 1024;
	}
	if(fMData_0 == 3){
	return fMemState_0A.dwAvailPageFile / 1024 / 1024 / 1024;
	}
	if(fMData_0 == 4){
		return (float)(fMemState_0A.dwAvailPhys / 1024 / 1024 / 1024);
	}
	if(fMData_0 == 5){
	return fMemState_0A.dwAvailVirtual / 1024 / 1024 / 1024;
	}
	if(fMData_0 == 6){
	return fMemState_0A.dwTotalPageFile / 1024 / 1024 / 1024;
	}
	if(fMData_0 == 7){
	return (float)(fMemState_0A.dwTotalPhys / 1024 / 1024 / 1024);
	}
	if(fMData_0 == 8){
	return fMemState_0A.dwTotalVirtual / 1024 / 1024 / 1024;
	}
}
int64_t fLTime(int64_t fLtData)
{
	SYSTEMTIME  fSys_time;
	GetLocalTime(&fSys_time);
	if(fLtData == 0){
	return fSys_time.wHour;
	}
	if(fLtData == 1){
	return fSys_time.wMinute;
	}
	if(fLtData == 2){
	return fSys_time.wSecond;
	}
	if (fLtData == 3) {
		return fSys_time.wMilliseconds;
	}
	
}
int64_t CPUArch()
{
	SYSTEM_INFO h_sys;
	GetSystemInfo(&h_sys);
	if(h_sys.wProcessorArchitecture == 9){
		return 64;
	}
	if(h_sys.wProcessorArchitecture == 6){
		return 32;
	}
}
std::string fCPUType()
{
	SYSTEM_INFO cpu;
	GetSystemInfo(&cpu);
	if(cpu.dwProcessorType == PROCESSOR_AMD_X8664){
		return "AMD x64";
	}
	if(cpu.dwProcessorType == PROCESSOR_INTEL_486){
		return "Intel x86";
	}
	else
	{
		return std::to_string(cpu.dwProcessorType);
	}
}
