
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <GL/GL.h>
#include <tchar.h>
#include <string>
#include "JoyStick.h"
#include <iostream>
#include <conio.h>
#include "dSys.h"
#include <fstream>
#include <Psapi.h>
#include <urlmon.h>//
#include <clocale>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "Colors.h"
#include <unordered_map>
#include <cstdarg>
#include "imgui_internal.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "cpudata.h"
#include "gpudata.h"
#include <chrono>
#include "MemorySys.h"
using namespace chrono;
//typedef int int128_t __attribute__((mode(TI)));
//typedef unsigned int uint128_t __attribute__((mode(TI)));
std::string ConsolePut(std::string data) {
    std::cout << data << std::endl;
    return "";
}
#pragma comment (lib , "Urlmon.lib")

#pragma once
namespace ImGui {
    bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        // Render
        window->DrawList->PathClear();

        int num_segments = 30;
        int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

        const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
        const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

        const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
            window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
                centre.y + ImSin(a + g.Time * 8) * radius));
        }

        window->DrawList->PathStroke(color, false, thickness);
    }
    bool InputInt8(const char* label, int8_t* v, int8_t step, int8_t step_fast, ImGuiInputTextFlags flags)
    {
        // Hexadecimal input provided as a convenience but the flag name is awkward. Typically you'd use InputText() to parse your own data, if you want to handle prefixes.
        const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
        return InputScalar(label, ImGuiDataType_S8, (void*)v, (void*)(step > 0 ? &step : NULL), (void*)(step_fast > 0 ? &step_fast : NULL), format, flags);
    }
    bool InputInt64(const char* label, int64_t* v, int64_t step, int64_t step_fast, ImGuiInputTextFlags flags)
    {
        // Hexadecimal input provided as a convenience but the flag name is awkward. Typically you'd use InputText() to parse your own data, if you want to handle prefixes.
        const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
        return InputScalar(label, ImGuiDataType_U64, (void*)v, (void*)(step > 0 ? &step : NULL), (void*)(step_fast > 0 ? &step_fast : NULL), format, flags);
    }
    bool InputUInt64(const char* label, uint64_t* v, uint64_t step, uint64_t step_fast, ImGuiInputTextFlags flags)
    {
        // Hexadecimal input provided as a convenience but the flag name is awkward. Typically you'd use InputText() to parse your own data, if you want to handle prefixes.
        const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
        return InputScalar(label, ImGuiDataType_U64, (void*)v, (void*)(step > 0 ? &step : NULL), (void*)(step_fast > 0 ? &step_fast : NULL), format, flags);
    }
    bool SliderInt64(const char* label, uint64_t* v, uint64_t v_min, uint64_t v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalar(label, ImGuiDataType_U64, v, &v_min, &v_max, format, flags);
    }

}
struct PerfomanceData {
    int64_t CommitLimit = (fPerfomanceInfo(1));
    int64_t CommitPeak = (fPerfomanceInfo(2));
    int64_t CommitTotal = (fPerfomanceInfo(3));
    int64_t KernelNonpaged = (fPerfomanceInfo(4));
    int64_t KernelPaged = (fPerfomanceInfo(5));
    int64_t KernelTotal = (fPerfomanceInfo(6));
    int64_t PageSize = (fPerfomanceInfo(7));
    int64_t PhysicalAvailable = (fPerfomanceInfo(8));
    int64_t PhysicalTotal = (fPerfomanceInfo(9));
    int64_t ProcessCount = fPerfomanceInfo(10);
    int64_t SystemCache = (fPerfomanceInfo(11));
    int64_t ThreadCount = fPerfomanceInfo(12);
};

class cpudata {
public:
    int64_t fcpu_data = GetProcessorSpeed();
    std::nano cpu_load;
    std::string fNUMANodes = std::to_string(dDataCPU(1));
    std::string fPhysNumberPackages = std::to_string(dDataCPU(2));
    std::string fCPUCores = std::to_string(dDataCPU(3));
    std::string fCPULogicalCores = std::to_string(dDataCPU(4));
    std::string fL3CacheSize = std::to_string(dDataCPU(5));
    std::string fL2CacheSize = std::to_string(dDataCPU(6));
    std::string fL1CacheSize = std::to_string(dDataCPU(7));
    std::string fL4CacheSize = std::to_string(dDataCPU(8));
    std::string fCPULoadPercent;
    std::string fCPUSpeed = std::to_string(fcpu_data) + " Mhz";
};
struct MemoryData {
    int64_t dwLenA = (fMemStatus(0));
    int64_t dwMemoryLoad = (fMemStatus(1));
    int64_t ullAvailExtendedVirtual = (fMemStatus(2));
    int64_t ullAvailPageFile = (fMemStatus(3));
    int64_t ullAvailPhys = (fMemStatus(4));
    int64_t ullAvailVirtual = (fMemStatus(5));
    int64_t ullTotalPageFile = (fMemStatus(6));
    int64_t ullTotalPhys = (fMemStatus(7));
    int64_t ullTotalVirtual = fMemStatus(8);
};
typedef double long float64_t;
class strData {
    // static int64_t int642str(int64_t integerData, std::string* fM_bufferArrayStr);
    // static int64_t const_char2str(const char* Data, std::string* fM_bufferArrayStr);
public:
    static int64_t int642str(int64_t integerData, std::string* fM_bufferArrayStr) {
        *fM_bufferArrayStr = (std::to_string(integerData)).c_str();
        return 1;
    }
    static int64_t const_char2str(const char* Data, std::string* fM_bufferArrayStr) {
        *fM_bufferArrayStr = Data;
        return 1;
    }
};
// Simple helper function to load an image into a OpenGL texture with common settings
PerfomanceData sInfo;
MemoryData mInfo;
strData ByteTransfer;
cpudata* CPU = new cpudata;
//
std::string strArray;

//fA_int2str(sInfo.CommitLimit,&strArray);
//
//..
float64_t g = 0;
static std::string fCommitLimit = std::to_string((int64_t)sInfo.CommitLimit) + " Bytes";
static std::string fCommitPeak = std::to_string((int64_t)sInfo.CommitPeak) + " Bytes";
static std::string fCommitTotal = std::to_string((int64_t)sInfo.CommitTotal) + " Bytes";
static std::string fKernelNonpaged = std::to_string((int64_t)sInfo.KernelNonpaged) + " Bytes";
static std::string fKernelPaged = std::to_string((int64_t)sInfo.KernelPaged) + " Bytes";
static std::string fKernelTotal = std::to_string((int64_t)sInfo.KernelTotal) + " Bytes";
static std::string fPageSize = std::to_string((int64_t)sInfo.PageSize) + " Bytes";
static std::string fPhysicalAvailable = std::to_string((int64_t)sInfo.PhysicalAvailable) + " Bytes";
static std::string fPhysicalTotal = std::to_string((int64_t)sInfo.PhysicalTotal) + " Bytes";
static std::string fProcessCount = std::to_string(sInfo.ProcessCount);
static std::string fSystemCache = std::to_string((int64_t)sInfo.SystemCache) + " Bytes";
static std::string fThreadCount = std::to_string(sInfo.ThreadCount);
// 
static std::string fdwLenA = std::to_string((int64_t)mInfo.dwLenA);
static std::string fdwMemoryLoad = (std::to_string((int64_t)mInfo.dwMemoryLoad) + "%%").c_str();
static std::string fGBMemoryLoad = std::to_string(fMemStatus(7) - fMemStatus(4)) + " GB";
static std::string fullAvailExtendedVirtual = std::to_string((int64_t)mInfo.ullAvailExtendedVirtual) + " GB";
static std::string fullAvailPageFile = std::to_string((int64_t)sInfo.CommitLimit - (int64_t)sInfo.CommitTotal) + "GB";
static std::string fullAvailPhys = std::to_string((int64_t)mInfo.ullAvailPhys) + "GB";
static std::string fullAvailVirtual = std::to_string((int64_t)mInfo.ullAvailVirtual) + "GB";
static std::string fullTotalPageFile = std::to_string((int64_t)mInfo.ullTotalPageFile) + "GB";
static std::string fullTotalPhys = std::to_string((int64_t)mInfo.ullTotalPhys) + "GB";
static std::string fullTotalVirtual = std::to_string((int64_t)mInfo.ullTotalVirtual) + "GB";
//
//
//
typedef long double double64_t;
static bool fCBenchMemory = false;
auto write_timeOut = 0;
double write_speedOut = 0;
auto read_timeOut = 0;
double read_speedOut = 0;
bool MemoryTestFrame = false;
uint64_t fMallocMemoryOffset = 1000;
//static std::string fTime = (std::to_string(tInfo.Hour) + ":" + std::to_string(tInfo.Min) + ":" + std::to_string(tInfo.Sec));
// Data stored per platform window
struct WGL_WindowData { HDC hDC; };

// Data
static HGLRC            g_hRC;
static WGL_WindowData   g_MainWindow;
static int              g_Width;
static int              g_Height;
ImVec4 clear_color = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);

// Forward declarations of helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data);

//
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int, char** argv)
{

    // AGPU->agsCheck();
     //ByteTransfer.int2str(123, &strArray);
    ByteTransfer.int642str(13, &strArray);
    g = 1, 3333;
    double64_t d;
    std::cout << "Test double64_t size:" << sizeof(d) << "data_test:" << g << std::endl;
    ImDrawListSplitter JEApp;

    char fInputBuffer;
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"System-Z 1.1(release) OpenGL3.3", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"System-Z 1.1(release) OpenGL3.3", WS_OVERLAPPEDWINDOW | WS_EX_TOOLWINDOW | WS_EX_NOPARENTNOTIFY, 100, 80, 600, 800, nullptr, nullptr, wc.hInstance, nullptr);
    ::SetWindowLongA(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
    // Initialize OpenGL
    AGPU->hwnd = hwnd;
    if (!CreateDeviceWGL(hwnd, &g_MainWindow))
    {
        CleanupDeviceWGL(hwnd, &g_MainWindow);
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }
    wglMakeCurrent(g_MainWindow.hDC, g_hRC);

    // Show the window
   // ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::AnimateWindow(hwnd, 100, AW_BLEND);
    ::ShowWindow(GetConsoleWindow(), 2);
    ::UpdateWindow(hwnd);
    std::string fStrParam;
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplOpenGL3_Init();
    io.Fonts->AddFontFromFileTTF(".\\SFMonoRegular.ttf", 18.0f);//
    ImFont* font40 = io.Fonts->AddFontFromFileTTF(".\\SFMonoRegular.ttf", 30.0f);
    ImFont* font60 = io.Fonts->AddFontFromFileTTF(".\\SFMonoRegular.ttf", 50.0f);
    struct GPU_DATA {
        std::string E_Brand = (const char*)glGetString(GL_VENDOR);
        std::string E_Model = (const char*)glGetString(GL_RENDERER);
        std::string E_GLVer = (const char*)glGetString(GL_VERSION);
    };
    GPU_DATA* GPU = new GPU_DATA;
    std::string fD_gpuBrand = GPU->E_Brand;
    std::string fD_gpuModel = GPU->E_Model;
    std::string fD_gpuGLVer = GPU->E_GLVer;
    //SetColorAMD64(240);

    DriveInfoNavigator driveInfoNavigator;

    ConsolePutColored(("OpenGL Vendor: " + fD_gpuBrand).c_str(), 240);
    ConsolePutColored(("OpenGL Renderer: " + fD_gpuModel), 240);
    ConsolePutColored(("OpenGL Version: " + fD_gpuGLVer), 240);
    // std::cout << "" << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "" << std::endl;
    int CPUInfo[4] = { -1 };
    unsigned   nExIds, i = 0;
    char CPUBrandString[0x40];
    // Get the information associated with each extended ID.
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];
    for (i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        // Interpret CPU brand string
        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    std::string dCPUBrandString = CPUBrandString;
    // Main loop
    bool main_logo = true;
    bool done = false;
    std::cout << "[JE_ENGINE] Main Frame Loaded!!" << std::endl;
    ConsolePut("---------------------------------\n::: CPU INFO :::");
    ConsolePut(("CPU:" + dCPUBrandString).c_str());
    ConsolePut(("NUMA Nodes:" + CPU->fNUMANodes).c_str());
    ConsolePut(("Physical CPU packages:" + CPU->fPhysNumberPackages).c_str());
    ConsolePut(("CPU cores:" + CPU->fCPUCores).c_str());
    ConsolePut(("Logical processors:" + CPU->fCPULogicalCores).c_str());
    ConsolePut(("L1 Cache:(not Correctly)" + CPU->fL1CacheSize + " MB").c_str());
    ConsolePut(("L2 Cache:(not Correctly)" + CPU->fL2CacheSize + " MB").c_str());
    ConsolePut(("L3 Cache:(not Correctly)" + CPU->fL3CacheSize + " MB").c_str());
    ConsolePut("---------------------------------\n::: GPU :::");
    ConsolePut(("GPU:" + (fD_gpuModel)).c_str());
    ConsolePut(("GPU GL:" + (fD_gpuGLVer)).c_str());
    ConsolePut("---------------------------------\n::: PERFOMANCE INFO :::");
    ConsolePut(("Commit Limit:" + (fCommitLimit)).c_str());
    ConsolePut(("Commit Peak:" + (fCommitPeak)).c_str());
    ConsolePut(("Commit Total:" + (fCommitTotal)).c_str());
    ConsolePut(("Kernel Non paged:" + (fKernelNonpaged)).c_str());
    ConsolePut(("Kernel Paged:" + (fKernelPaged)).c_str());
    ConsolePut(("Kernel Total:" + (fKernelTotal)).c_str());
    ConsolePut(("Page Size:" + (fPageSize)).c_str());
    ConsolePut(("Physical Available:" + (fPhysicalAvailable)).c_str());
    ConsolePut(("Physical Total:" + (fPhysicalTotal)).c_str());
    ConsolePut(("Process Count:" + (fProcessCount)).c_str());
    ConsolePut(("System Cache:" + (fSystemCache)).c_str());
    ConsolePut(("Thread Count:" + (fThreadCount)).c_str());
    ConsolePut("---------------------------------\n::: MEMORY INFO :::");
    ConsolePut(("Memory Load:" + (fdwMemoryLoad)+"/" + fGBMemoryLoad).c_str());
    ConsolePut(("Free Memory:" + (fullAvailPhys)).c_str());
    ConsolePut(("Total Memory:" + (fullTotalPhys)).c_str());

    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        bool fB_loadFrame = false;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                exit(0);
            //  done = true;
            if (msg.message == WM_DESTROY)
                exit(0);
        }

        if (done)
            break;
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            bool fJEFrame = true;
            char intBuffer;
            JEApp.ClearFreeMemory();
            ImGuiStyle& style = ImGui::GetStyle();
            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.53f, 0.53f, 0.53f, 1.0f);
            style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 0.00f, 0.50f, 0.00f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 0.80f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.0f, .50f, 1.0f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.0f, .50f, 1.0f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
            style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
            ImGuiButtonFlags btn_flags = ImGuiButtonFlags_MouseButtonMask_;
            style.FrameBorderSize = 1;

        }

        bool b_vsync = true;
        if (argv[1] == "vsync=true") {
            b_vsync = true;
        }
        if (argv[1] == "vsync=false") {
            b_vsync = true;
        }
        //struct TimeOffset {
        int64_t Hour = fLTime(0);
        int64_t Min = fLTime(1);
        int64_t Sec = fLTime(2);
        // };

         //TimeOffset tInfo;
        static std::string fTime = (std::to_string(Hour) + ":" + std::to_string(Min) + ":" + std::to_string(Sec));
        JEApp.ClearFreeMemory();
        if (b_vsync) {
            Sleep(13);
            // WriteConfigJE << "fJEVsync=true;" << std::endl;
        }
        else {
            Sleep(0);
            // WriteConfigJE << "fJEVsync=false;" << std::endl;
        }
        bool bSwitchBool = true;
        static  bool loadingWindow = false;
        static int64_t uLoad = 0;
        static int64_t uLexit = 0;
        static uint64_t ldColorSpinner = 0;
        static bool exitWindow = false;
        ImU32 col = 0;

        if (bSwitchBool) {
            if (main_logo) {

                // ConsolePut("INFO: Main Frame Open");
                JEApp.ClearFreeMemory();
                ImGui::Begin("LOGO", &main_logo, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
                // CurrentWindowSizeW(AGPU->hwnd, &AGPU->wx, &AGPU->wy);
                ImGui::SetWindowSize(ImVec2(AGPU->wx, AGPU->wy));
                ldColorSpinner++;
                if (ldColorSpinner >= 0) {
                    col = ImGui::GetColorU32(ImVec4(0.0f, 1, 0.50f, 1.0f));
                }
                if (ldColorSpinner >= 3) {
                    col = ImGui::GetColorU32(ImVec4(0.20f, 0.60f, 1.0f, 1.0f));
                }
                if (ldColorSpinner >= 6) {
                    col = ImGui::GetColorU32(ImVec4(0.50f, 0, 1.0f, 1.0f));
                }
                if (ldColorSpinner > 6) {
                    ldColorSpinner = 0;
                }
                static std::string fGlichText;
                AGPU->SYSTEM_Z(&fGlichText);
                ImGui::SetWindowPos(ImVec2(-2, 1));
                ImGui::SetCursorPos(ImVec2(103, 179));
                ImGui::PushFont(font60);
                ImGui::Text((fGlichText).c_str());
                ImGui::PopFont();
                if (!loadingWindow) {
                    if (!exitWindow)
                    {
                        // ConsolePut("INFO: Loading no Open");
                        ImGui::SetCursorPosX(83);
                        ImGui::Text("used AMD_AGS_x64 (C++20) (Work Only AMD GPU)");
                        ImGui::SetCursorPosX(103);
                        ImGui::TextColored(ImVec4(1.0f, 0, 0.50f, 1.0f), "(Full GPU Info only AMD GPU)");
                        ImGui::SetCursorPosX(133);
                        ImGui::Text("System Hardware info Test");
                        ImGui::SetCursorPosX(133);
                        ImGui::Text("Writtein to C++20 x64");
                        ImGui::SetCursorPosX(133);
                        ImGui::Text("Backend API: OpenGL3.3");
                        ImGui::SetCursorPosX(133);
                        ImGui::Text("Created by HCPP");
                        ImGui::SetCursorPosX(133);
                        if (ImGui::Button("START", ImVec2(250.0f, 30.0f))) {
                            AGPU->agsCheck();

                            loadingWindow = true;
                        }
                    }
                }
                if (exitWindow) {
                    //ConsolePut("INFO: Exiting");
                    loadingWindow = false;
                    main_logo = true;
                    uLexit++;
                    ImGui::SetCursorPos(ImVec2(103, 229));
                    ImGui::PushFont(font60);
                    ImGui::Text("Exiting..");
                    ImGui::PopFont();
                    ImGui::SetCursorPos(ImVec2(233, 299));
                    ImGui::Spinner("Loading data", 20, 4, col);
                    if (uLexit == 100) {
                        ClearMemoryAddress();
                        exit(0);
                    }
                }
                if (loadingWindow) {
                    // ConsolePut("INFO: Loading Open");
                    uLoad++;
                    ImGui::SetCursorPos(ImVec2(123, 269));
                    ImGui::Text((AGPU->GPUInitMsg).c_str());
                    ImGui::SetCursorPos(ImVec2(233, 340));
                    ImGui::Spinner("Loading data", 20, 4, col);
                    if (uLoad == 100) {
                        main_logo = false;
                        loadingWindow = false;
                    }
                }

                ImGui::End();
            }
            if (!main_logo) {

                loadingWindow = false;
                JEApp.ClearFreeMemory();
                ImGui::Begin("Main Info", &main_logo, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
                //ImGui::Text(("mem_usage:" + std::to_string(((fDataMemUsage() / 1024) / 1024))).c_str());
               // CurrentWindowSizeW(AGPU->hwnd, &AGPU->wx, &AGPU->wy);
                ImGui::SetWindowSize(ImVec2(AGPU->wx, AGPU->wy));
                if (!exitWindow) {
                    if (ImGui::Button("EXIT", ImVec2(150.0f, 30.0f))) {
                        //code = AGS_FAILURE;
                      //  AGPU->agsCheck();
                        exitWindow = true;
                        main_logo = true;

                    }
                }

                static bool bCPU_Bench = false;
                static bool hashGenStart = false;
                static double endHashTime2;
                ImGui::SameLine();
                if (ImGui::Button("BACK", ImVec2(100.0f, 30.0f))) {
                    main_logo = true;
                    uLoad = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("Memory Bench", ImVec2(150.0f, 30.0f))) {
                    fCBenchMemory = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("CPU Bench", ImVec2(150.0f, 30.0f))) {
                    hashGenStart = true;
                }
                static std::string gpuCoreClock;
                static std::string gpuMemClock;
                static std::string gpuLocalMemory;
                static std::string gpuSharedMemory;
                static std::string gpuNumberCUs;
                static std::string gpuNumberROPs;
                static std::string gpuNumberWGPs;
                static std::string gpuMemoryBandwidth;
                static std::string gpuTeraFlopsOffset;
                //
                static uint64_t fM_cpuCount = 0;
                static uint64_t fM_randSeed = 0;
                static uint64_t fM_score = 0;
                //
                std::string fM_strBuffer;
                std::string fM_CharsBuffer = "1234567890-=qwertyuiop[]asdfgghjkl;'zxcvbnmm,,./QWERTYUIOP{}ASDGHJKL:ZXCVBNM<>";

                ImGui::SeparatorText("CPU Hash Bench");
                if (hashGenStart) {
                    srand(time(0));
                    auto t0 = high_resolution_clock::now();
                    for (uint64_t chk = 0; chk <= 3000000; chk++) {
                        fM_strBuffer += fM_CharsBuffer[rand() % fM_CharsBuffer.size()];
                    }

                    auto t1 = high_resolution_clock::now();
                    double endHashTime = duration_cast<milliseconds>(t1 - t0).count();
                    endHashTime2 = endHashTime;
                    hashGenStart = false;
                }

                ImGui::Text("Elapset Time to Hash Gen: %.2f ms", endHashTime2);

                if (AGPU->GPUNotAMD) {
                    gpuCoreClock = std::to_string(AGPU->GPUCoreClock) + ": Mhz";
                    gpuMemClock = std::to_string(AGPU->GPUMemoryClock) + ": Mhz";
                    gpuLocalMemory = std::to_string((AGPU->GPUlocalMemory / 1024) / 1024 / 1024) + "GB";
                    gpuSharedMemory = std::to_string((AGPU->GPUSharedMemory / 1024) / 1024 / 1024) + "GB";
                    gpuNumberCUs = std::to_string(AGPU->GPUNumberCUs);
                    gpuNumberROPs = std::to_string(AGPU->GPUNumberROPs);
                    gpuNumberWGPs = std::to_string(AGPU->GPUNumberWGPs);
                    gpuMemoryBandwidth = std::to_string(AGPU->GPUMemoryBandwidth) + " GB/s";
                    gpuTeraFlopsOffset = std::to_string(AGPU->GPUTeraFlops) + " TFlops";
                }

                ImGui::SetWindowPos(ImVec2(-3, -2));
                ImGui::SeparatorText("CPU INFO");
                ImGui::Text(("CPU:" + dCPUBrandString).c_str());
                ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), ("NUMA Nodes:" + CPU->fNUMANodes).c_str()); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), ("CPU Speed:" + CPU->fCPUSpeed).c_str());
                ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), ("Physical CPU packages:" + CPU->fPhysNumberPackages).c_str()); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), ("CPU cores:" + CPU->fCPUCores).c_str());
                ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), ("Logical processors:" + CPU->fCPULogicalCores).c_str());
                ImGui::SeparatorText("GPU INFO");
                ImGui::Text(("GPU:" + (fD_gpuModel)).c_str()); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), "%.2f GB", AGPU->GPUlocalMemory / 1024 / 1024 / 1024);
                ImGui::Text(("GPU GL:" + (fD_gpuGLVer)).c_str());
                if (!AGPU->GPUNotAMD) {
                    ImGui::Text("You GPU not Supported!! Error: gpuStack:%p", &gpuInfo.devices[gpuIndex]);
                }

                if (AGPU->GPUNotAMD) {
                    ImGui::SeparatorText("Compute Units (Only AMD) AMD_AGS_SDK Metrics)");
                    ImGui::Columns(2, "##GpuData", true);
                    ImGui::Text((" CUs:" + gpuNumberCUs).c_str());
                    ImGui::Text((" ROPs:" + gpuNumberROPs).c_str());
                    ImGui::Text((" Clock:" + gpuCoreClock).c_str());
                    ImGui::Text((" WGPs:" + gpuNumberWGPs).c_str());
                    ImGui::NextColumn();
                    ImGui::Text((" MemoryBandwidth:" + gpuMemoryBandwidth).c_str());
                    ImGui::Text((" Mem Shared:" + gpuSharedMemory).c_str());
                    ImGui::Text((" Mem Clock:" + gpuMemClock).c_str());
                    ImGui::Text((" TFlops:" + gpuTeraFlopsOffset).c_str());
                    ImGui::Columns(1);
                }
                ImGui::SeparatorText("HDD/SSD Info (fix crash https://github.com/Esewqe' )");
                ImGui::Text("Drives: %d", driveInfoNavigator.totalDrives);  ImGui::SameLine();
                ImGui::Text((driveInfoNavigator.selectedType).c_str()); ImGui::SameLine();
                ImGui::Text((driveInfoNavigator.selectedName).c_str()); ImGui::SameLine();
                ImGui::Text((driveInfoNavigator.selectedTotalSize + " / " + driveInfoNavigator.selectedFreeSpaceSize).c_str());;
                // ImGui::SameLine();

                if (ImGui::Button("<", ImVec2(30.0f, 30.0f))) {
                    driveInfoNavigator.Prev();
                }

                ImGui::SameLine();

                if (ImGui::Button(">", ImVec2(30.0f, 30.0f))) {
                    driveInfoNavigator.Next();
                }

                // ImGui::Text(DiskData->msg);
                ImGui::SeparatorText("MEMORY INFO");
                ImGui::Text(("Memory Load:" + (fdwMemoryLoad)+"/" + fGBMemoryLoad).c_str());
                ImGui::Text(("Free Memory:" + (fullAvailPhys)).c_str());
                ImGui::Text(("Total Memory:" + (fullTotalPhys)).c_str());

                ImGui::SeparatorText("MEMORY BENCH");
                ImGui::SliderInt64((std::to_string((fMallocMemoryOffset) * 8) + "MB").c_str(), &fMallocMemoryOffset, 1, 5000, "", 0);
                ImGui::Columns(2, "##BenchTests", true);
                ImGui::Text("Write test:");
                ImGui::Text("Time: %d ms", write_timeOut);
                ImGui::Text("Speed:%.2f GB/S", write_speedOut);
                ImGui::NextColumn();
                ImGui::Text("Read test:");
                ImGui::Text("Time:%d ms ", read_timeOut);
                ImGui::Text("Speed: %.2f GB/S", read_speedOut);
                ImGui::Columns(1);
                if (fCBenchMemory) {
                    MessageBoxA(hwnd, ("[WARNING]The process cannot be stopped\nThe benchmark consumes " + std::string(std::to_string((fMallocMemoryOffset) * 8)) + " MB of RAM").c_str(), "SYSTEM-Z::Memory Test", 1);
                    uint64_t buffer_size = (fMallocMemoryOffset) * 1024 * 1024;
                    const uint64_t GB = 1024 * 1024 * 1024;

                    // Выделение памяти
                    uint64_t* buffer = nullptr;
                    try {
                        buffer = new uint64_t[buffer_size];
                    }
                    catch (const bad_alloc& e) {
                        ImGui::TextColored(ImVec4(1.0f, 0, 0.40f, 1.0f), "Memory allocation failed: %d", e.what());
                        MessageBoxA(hwnd, ("Memory allocation failed:\nError:" + std::string(e.what())).c_str(), "SYSTEM-Z::Memory Test", 1);
                        return EXIT_FAILURE;
                    }

                    // Тест записи
                   // std::ofstream dumpMemory("MemoryDump.txt");
                    auto write_start = high_resolution_clock::now();
                    for (uint64_t i = 0; i < buffer_size; i++) {
                        buffer[i] = static_cast<uint64_t>(i % 256);

                    }
                    auto write_end = high_resolution_clock::now();

                    // Тест чтения и проверки
                    auto read_start = high_resolution_clock::now();
                    for (uint64_t i = 0; i < buffer_size; i++) {

                        if (buffer[i] != static_cast<uint64_t>(i % 256)) {
                            MessageBoxA(hwnd, ("Memory verification failed at position " + std::to_string(i)).c_str(), "SYSTEM-Z::Memory Test", 1);
                            cerr << "Memory verification failed at position " << i << endl;
                            delete[] buffer;
                            fCBenchMemory = false;
                            return EXIT_FAILURE;

                        }
                    }
                    auto read_end = high_resolution_clock::now();

                    // Освобождение памяти
                    delete[] buffer;
                    ///dumpMemory.close();
                    // Расчёт и вывод результатов
                    int64_t write_time = duration_cast<milliseconds>(write_end - write_start).count();
                    int64_t read_time = duration_cast<milliseconds>(read_end - read_start).count();

                    double write_speed = static_cast<double>(buffer_size) / GB / (write_time / 1000.0);
                    double read_speed = static_cast<double>(buffer_size) / GB / (read_time / 1000.0);
                    //
                    write_timeOut = write_time;
                    read_timeOut = read_time;
                    write_speedOut = write_speed;
                    read_speedOut = read_speed;
                    fCBenchMemory = false;
                    // cout << "Read test:" << endl;
                    // cout << " - Time: " << read_time << " ms" << endl;
                    // cout << " - Speed: " << read_speed << " MB/s" << endl;
                     //fCBenchMemory = false;
                }
                ImGui::End();
            }
        }
        // ImGui::End();

 // Rendering
        ImGui::Render();
        glViewport(0, 0, 400, 800);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Present
        ::SwapBuffers(g_MainWindow.hDC);

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceWGL(hwnd, &g_MainWindow);
    wglDeleteContext(g_hRC);
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    HDC hDc = ::GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0)
        return false;
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
        return false;
    ::ReleaseDC(hWnd, hDc);

    data->hDC = ::GetDC(hWnd);
    if (!g_hRC)
        g_hRC = wglCreateContext(data->hDC);
    return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    wglMakeCurrent(nullptr, nullptr);
    ::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            g_Width = LOWORD(lParam);
            g_Height = HIWORD(lParam);
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        exit(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
