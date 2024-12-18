
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
//#include "JoyStick.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <Psapi.h>
#include <urlmon.h>
#include "dSys.h"
#include <clocale>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include "Colors.h"
#pragma comment (lib , "Urlmon.lib")
uint64_t fDataMemUsage() // Work Function !!! Check Sym RAM to Current Program //
{
    PROCESS_MEMORY_COUNTERS pmc;
    pmc.cb = sizeof(pmc);
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}

#pragma once


struct PerfomanceData {
    int64_t CommitLimit = fPerfomanceInfo(1);
    int64_t CommitPeak = fPerfomanceInfo(2);
    int64_t CommitTotal = fPerfomanceInfo(3);
    int64_t KernelNonpaged = fPerfomanceInfo(4);
    int64_t KernelPaged = fPerfomanceInfo(5);
    int64_t KernelTotal = fPerfomanceInfo(6);
    int64_t PageSize = fPerfomanceInfo(7);
    int64_t PhysicalAvailable = fPerfomanceInfo(8);
    int64_t PhysicalTotal = fPerfomanceInfo(9);
    int64_t ProcessCount = fPerfomanceInfo(10);
    int64_t SystemCache = fPerfomanceInfo(11);
    int64_t ThreadCount = fPerfomanceInfo(12);
};
struct MemoryData {
    int64_t dwLenA = fMemStatus(0);
    int64_t dwMemoryLoad = fMemStatus(1);
    int64_t ullAvailExtendedVirtual = fMemStatus(2);
    int64_t ullAvailPageFile = fMemStatus(3);
    int64_t ullAvailPhys = fMemStatus(4);
    int64_t ullAvailVirtual = fMemStatus(5);
    int64_t ullTotalPageFile = fMemStatus(6);
    int64_t ullTotalPhys = fMemStatus(7);
    int64_t ullTotalVirtual = fMemStatus(8);
};
struct TimeOffset {
    int64_t Hour = fLTime(0);
    int64_t Min = fLTime(1);
    int64_t Sec = fLTime(2);
};

   static int64_t int2str(int64_t integerData ,std::string *fM_bufferArrayStr) {
        *fM_bufferArrayStr =  std::to_string(integerData);
        return 1;
    }
// Simple helper function to load an image into a OpenGL texture with common settings

PerfomanceData sInfo;
MemoryData mInfo;
TimeOffset tInfo;
//
//
static std::string fCommitLimit = std::to_string(sInfo.CommitLimit);
static std::string fCommitPeak = std::to_string(sInfo.CommitPeak);
static std::string fCommitTotal = std::to_string(sInfo.CommitTotal);
static std::string fKernelNonpaged = std::to_string(sInfo.KernelNonpaged);
static std::string fKernelPaged = std::to_string(sInfo.KernelPaged);
static std::string fKernelTotal = std::to_string(sInfo.KernelTotal);
static std::string fPageSize = std::to_string(sInfo.PageSize);
static std::string fPhysicalAvailable = std::to_string(sInfo.PhysicalAvailable);
static std::string fPhysicalTotal = std::to_string(sInfo.PhysicalTotal);
static std::string fProcessCount = std::to_string(sInfo.ProcessCount);
static std::string fSystemCache = std::to_string(sInfo.SystemCache);
static std::string fThreadCount = std::to_string(sInfo.ThreadCount);
// 
static std::string fdwLenA = std::to_string(mInfo.dwLenA);
static std::string fdwMemoryLoad = std::to_string(mInfo.dwMemoryLoad);
static std::string fullAvailExtendedVirtual = std::to_string(mInfo.ullAvailExtendedVirtual);
static std::string fullAvailPageFile = std::to_string(mInfo.ullAvailPageFile);
static std::string fullAvailPhys = std::to_string(mInfo.ullAvailPhys);
static std::string fullAvailVirtual = std::to_string(mInfo.ullAvailVirtual);
static std::string fullTotalPageFile = std::to_string(mInfo.ullTotalPageFile);
static std::string fullTotalPhys = std::to_string(mInfo.ullTotalPhys);
static std::string fullTotalVirtual = std::to_string(mInfo.ullTotalVirtual);
//
static std::string fTime = (std::to_string(tInfo.Hour) + ":" + std::to_string(tInfo.Min) + ":" + std::to_string(tInfo.Sec));
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


int main(int, char**)
{
    
    ImDrawListSplitter JEApp;
    
     char fInputBuffer;
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"System-Z 0.1 OpenGL3.3", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"System-Z 0.1 OpenGL3.3", WS_OVERLAPPEDWINDOW | WS_EX_TOOLWINDOW |  WS_EX_NOPARENTNOTIFY, 100, 80, 500, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize OpenGL
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
        io.Fonts->AddFontFromFileTTF(".\\WhiteRabbit.ttf", 15.0f);//
    std::cout << "[JE_ENGINE] Loaded Font WhiteRabbit.ttf" << std::endl;
    struct GPU_DATA {
        std::string E_Brand = (const char*)glGetString(GL_VENDOR);
        std::string E_Model = (const char*)glGetString(GL_RENDERER);
        std::string E_GLVer = (const char*)glGetString(GL_VERSION);
    };
    GPU_DATA GPU;
    std::string fD_gpuBrand = GPU.E_Brand;
    std::string fD_gpuModel = GPU.E_Model;
    std::string fD_gpuGLVer = GPU.E_GLVer;
    std::cout << "[JE_ENGINE] OpenGL Driver Loaded" << std::endl;
    //SetColorAMD64(240);
    std::cout << "" << std::endl;
    std::cout << "" << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "" << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "" << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
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
    bool done = false;
    std::cout << "[JE_ENGINE] Main Frame Loaded!!" << std::endl;
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
           // std::cout << "[JE_ENGINE] Frame Cra" << std::endl;
            std::exception *d;
            int64_t a, b;
          //  std::cout << "ADDR:" << &d << "->" << d << std::endl;
          //  ImGui::Begin("\tJE x64_OpenGL3_SSE4.2 C++20",&fJEFrame, ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoTitleBar);  
                // Create a window called "Hello, world!" and append into it.
                ImGui::SetWindowPos(ImVec2(6.0f, 19.0f));
                ImGui::SetWindowSize(ImVec2(475.0f, 703.0f));
                JEApp.ClearFreeMemory();
                    ImGuiStyle& style = ImGui::GetStyle();
                    style.ButtonTextAlign = ImVec2(0.2f, 0.5f);
                    style.WindowRounding = 5.3f;
                    style.FrameRounding = 2.3f;
                    style.ScrollbarRounding = 0;
                    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.106f, 0.106f, 0.118f, 0.80f);
                    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
                    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
                    style.Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
                    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.1f, 0.1f, 0.1f);
                    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
                    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
                    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.33f, 0.90f);
                    style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 0.0f, 0.33f, 0.90f);
                    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.004f, 0.016f, 0.035f, 1.0f);
                    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
                    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.0f, 0.0f, 0.33f, 0.90f);
                    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.0f, 0.20f, 0.373f, 1.0f);
                    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
                    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
                    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
                    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
                    style.Colors[ImGuiCol_Button] = ImVec4(1.0f, 0.0f, 0.33f, 0.90f);
                    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
                    style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.0f, 0.33f, 0.90f);
                    style.Colors[ImGuiCol_Header] = ImVec4(0.004f, 0.016f, 0.035f, 1.0f);
                    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 0.0f, 0.33f, 0.90f);
                    style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.0f, 0.0f, 0.33f, 0.90f);
                    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
                    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
                    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
                    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.20f, 0.373f, 1.0f);
                    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.20f, 0.373f, 0.90f);
                    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
                    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
                    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
                    ImGuiButtonFlags btn_flags = ImGuiButtonFlags_MouseButtonMask_;
                    
                }
         bool b_vsync = true;
                JEApp.ClearFreeMemory();
                if (b_vsync) {
                    Sleep(13);
                   // WriteConfigJE << "fJEVsync=true;" << std::endl;
                }
                else {
                    Sleep(0);
                   // WriteConfigJE << "fJEVsync=false;" << std::endl;
                }
              
                    ImGui::Begin("Main Info");
                    ImGui::Text(("SYSTEM-Z 0.2 " + fTime).c_str());
                    ImGui::SetWindowPos(ImVec2(6.0f, 19.0f));
                    ImGui::SetWindowSize(ImVec2(475.0f, 103.0f));
                    ImGui::Text(("CPU:" + dCPUBrandString).c_str());
                    ImGui::Text(("GPU:" + (fD_gpuModel)).c_str());
                    ImGui::Text(("GPU GL:" + (fD_gpuGLVer)).c_str());
                    ImGui::End();
                    ImGui::Begin("Perfomance Info");
                    ImGui::SetWindowPos(ImVec2(6.0f, 127.0f));
                    ImGui::SetWindowSize(ImVec2(475.0f, 303.0f));
                    ImGui::Text(("Commit Limit:" + (fCommitLimit)).c_str());
                    ImGui::Text(("Commit Peak:" + (fCommitPeak)).c_str());
                    ImGui::Text(("Commit Total:" + (fCommitTotal)).c_str());
                    ImGui::Text(("Kernel Non paged:" + (fKernelNonpaged)).c_str());
                    ImGui::Text(("Kernel Paged:" + (fKernelPaged)).c_str());
                    ImGui::Text(("Kernel Total:" + (fKernelTotal)).c_str());
                    ImGui::Text(("Page Size:" + (fPageSize)).c_str());
                    ImGui::Text(("Physical Available:" + (fPhysicalAvailable)).c_str());
                    ImGui::Text(("Physical Total:" + (fPhysicalTotal)).c_str());
                    ImGui::Text(("Process Count:" + (fProcessCount)).c_str());
                    ImGui::Text(("System Cache:" + (fSystemCache)).c_str());
                    ImGui::Text(("Thread Count:" + (fThreadCount)).c_str());
                    ImGui::End();
                    ImGui::Begin("Memory");
                    ImGui::SetWindowPos(ImVec2(6.0f, 437.0f));
                    ImGui::SetWindowSize(ImVec2(475.0f, 203.0f));
                    ImGui::Text(("dw Len:" + (fdwLenA)).c_str());
                    ImGui::Text(("dw Memory Load:" + (fdwMemoryLoad)).c_str());
                    ImGui::Text(("Avail Extended Virtual:" + (fullAvailExtendedVirtual)).c_str());
                    ImGui::Text(("Avail Page File:" + (fullAvailPageFile)).c_str());
                    ImGui::Text(("Avail Phys:" + (fullAvailPhys)).c_str());
                    ImGui::Text(("Avail Virtual:" + (fullAvailVirtual)).c_str());
                    ImGui::Text(("Total Page File:" + (fullTotalPageFile)).c_str());
                    ImGui::Text(("Total Phys:" + (fullTotalPhys)).c_str());
                    ImGui::Text(("Total Virtual:" + (fullTotalVirtual)).c_str());
                    ImGui::End();
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
