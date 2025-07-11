
#include <windows.h>
#include <malloc.h>    
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <vector>
#include <intrin.h>
#include <wtypes.h>
#include <vector>
#include <omp.h>
#pragma intrinsic(__rdtsc)
int64_t dDataCPU(int64_t fCode);
class CPUInfo { public: float dCPUSpeedMHz; int64_t i64CPUThreadOMP = omp_get_num_threads(); };
auto pInfo = std::make_unique<CPUInfo>();
int64_t GetProcessorSpeed()
{
    LARGE_INTEGER qwWait, qwStart, qwCurrent;
    QueryPerformanceCounter(&qwStart);
    QueryPerformanceFrequency(&qwWait);
    qwWait.QuadPart >>= 5;
    unsigned __int64 Start = __rdtsc();
    do
    {
        QueryPerformanceCounter(&qwCurrent);
    } while (qwCurrent.QuadPart - qwStart.QuadPart < qwWait.QuadPart);
    pInfo->dCPUSpeedMHz = ((__rdtsc() - Start) << 5) / 1000000.0;
    return pInfo->dCPUSpeedMHz;
}

void SaveHash(std::string data) {
    std::ofstream hashFile("CPUHash.txt");
    hashFile.is_open();
    hashFile << data << std::endl;
}
int64_t i64MSize = 0;
std::string *strBff;
std::string hashFn(int64_t sz) {
    std::string bff;
    const std::string bff_chr = "qwertyuiop[]asdfghjkl;'zxcvbnm,./12345678890";
    int64_t sd_rd = 0;
    srand(time(0));
    for (int64_t i = 0; i < sz; i++) {
        sd_rd = rand() % bff_chr.size();
        bff += bff_chr[sd_rd];

    }
    i64MSize += bff.size();
    return "Hash Size:"+std::to_string(bff.size());
}
int64_t GenHashToAllThreads() {
    int64_t i64HashSize = 3000000;
    int64_t i64HashChunk = i64HashSize / dDataCPU(4);
    std::jthread th(hashFn, i64HashChunk);
    std::jthread th1(hashFn, i64HashChunk);
    std::jthread th2(hashFn, i64HashChunk);
    std::jthread th3(hashFn, i64HashChunk);
    std::jthread th4(hashFn, i64HashChunk);
    std::jthread th5(hashFn, i64HashChunk);
    std::jthread th6(hashFn, i64HashChunk);
    std::jthread th7(hashFn, i64HashChunk);
    std::jthread th8(hashFn, i64HashChunk);
    std::jthread th9(hashFn, i64HashChunk);
    std::jthread th10(hashFn, i64HashChunk);
    std::jthread th11(hashFn, i64HashChunk);
    std::jthread th12(hashFn, i64HashChunk);
    std::jthread th13(hashFn, i64HashChunk);
    std::jthread th14(hashFn, i64HashChunk);
    std::jthread th15(hashFn, i64HashChunk);
    std::jthread th16(hashFn, i64HashChunk);
}
uint64_t ReadAddressToMemory(int8_t addr, int8_t* outData)// Not Correct Work Function !!! Check Sym VRAM to Current Program //
{
    *outData = (int8_t)(int8_t*)(addr);
   // __builtin_frame_address(0);
    return 0;
}
typedef BOOL(WINAPI* LPFN_GLPI)(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
    PDWORD);


// Helper function to count set bits in the processor mask.
DWORD CountSetBits(ULONG_PTR bitMask) //  Work Function !!! Set count Bits //
{
    DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest) ? 1 : 0);
        bitTest /= 2;
    }

    return bitSetCount;
}
int64_t dDataCPU(int64_t fCode)
{
    LPFN_GLPI glpi;
    BOOL done = FALSE;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
    DWORD returnLength = 0;
    DWORD logicalProcessorCount = 0;
    DWORD numaNodeCount = 0;
    DWORD processorCoreCount = 0;
    DWORD processorL1CacheCount = 0;
    DWORD processorL2CacheCount = 0;
    DWORD processorL3CacheCount = 0;
    DWORD processorPackageCount = 0;
    DWORD processorL4CacheCount = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    glpi = (LPFN_GLPI)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),
        "GetLogicalProcessorInformation");
    if (NULL == glpi)
    {
        _tprintf(TEXT("\n[CPU]GetLogicalProcessorInformation is not supported.\n"));
        return (1);
    }

    while (!done)
    {
        DWORD rc = glpi(buffer, &returnLength);

        if (FALSE == rc)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer)
                    free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
                    returnLength);

                if (NULL == buffer)
                {
                    _tprintf(TEXT("\nError: Allocation failure\n"));
                    return (2);
                }
            }
            else
            {
                _tprintf(TEXT("\nError %d\n"), GetLastError());
                return (3);
            }
        }
        else
        {
            done = TRUE;
        }
    }

    ptr = buffer;
    uint64_t l1offset = 0;
    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
    {
        switch (ptr->Relationship)
        {
        case RelationNumaNode:
            // Non-NUMA systems report a single record of this type.
            numaNodeCount++;
            break;

        case RelationProcessorCore:
            processorCoreCount++;

            // A hyperthreaded core supplies more than one logical processor.
            logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
            break;

        case RelationCache:
            // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
            Cache = &ptr->Cache;
          
            if (Cache->Level == 1)
            {
              // std::cout << "test size:" << Cache->Size << std::endl;
                processorL1CacheCount++;
            }
            else if (Cache->Level == 2)
            {
                processorL2CacheCount++;
            }
            else if (Cache->Level == 3)
            {
                processorL3CacheCount++;
            }
            else if (Cache->Level == 4)
            {
                processorL4CacheCount++;
            }
            break;

        case RelationProcessorPackage:
            // Logical processors share a physical package.
            processorPackageCount++;
            break;

        default:
            _tprintf(TEXT("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n"));
            break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }

    //    _tprintf(TEXT("\nGetLogicalProcessorInformation results:\n"));
    //    _tprintf(TEXT("Number of NUMA nodes: %d\n"), 
    //             numaNodeCount);
    //    _tprintf(TEXT("Number of physical processor packages: %d\n"), 
    //             processorPackageCount);
    //    _tprintf(TEXT("Number of processor cores: %d\n"), 
    //             processorCoreCount);
    //    _tprintf(TEXT("Number of logical processors: %d\n"), 
    //             logicalProcessorCount);
    //    _tprintf(TEXT("Number of processor L1/L2/L3 caches: %d/%d/%d\n"), 
    //             processorL1CacheCount,
    //             processorL2CacheCount,
    //             processorL3CacheCount);
    if (fCode == 1)
    {
        return numaNodeCount;
    }
    if (fCode == 2)
    {
        return processorPackageCount;
    }
    if (fCode == 3)
    {
        return processorCoreCount;
    }
    if (fCode == 4)
    {
        return logicalProcessorCount;
    }
    if (fCode == 5)
    {
        return processorL1CacheCount;
    }
    if (fCode == 6)
    {
        return processorL2CacheCount;
    }
    if (fCode == 7)
    {
        return processorL3CacheCount;
    }
    if (fCode == 8) {
        return processorL4CacheCount;
    }
    free(buffer);

    return 0;
}
