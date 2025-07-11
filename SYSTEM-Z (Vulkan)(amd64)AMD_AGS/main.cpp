
#include "imgui.h"
#define VK_USE_PLATFORM_WIN32_KHR
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

std::ofstream dumpMemory("SYSTEM_Z_Log.txt");
//typedef unsigned int uint128_t __attribute__((mode(TI)));
std::string ConsolePut(std::string data) {
   dumpMemory << data << std::endl;
    return "";
}
#pragma comment (lib , "Urlmon.lib")
void StyleColorGitHubLight() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    // Основные цвета
    colors[ImGuiCol_Text] = ImVec4(0.40f, 0.0f, 1.01f, 1.00f); // Темно-серый текст
    colors[ImGuiCol_WindowBg] = ImVec4(0.96f, 0.96f, 0.96f, 0.0f); // Светло-серый фон
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);

    // Фреймы и границы
    colors[ImGuiCol_Border] = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.0f); // Белый фон полей ввода
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.95f, 1.00f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.95f, 1.00f, 0.45f);

    // Заголовки
    colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    // Кнопки
    colors[ImGuiCol_Button] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

    // Акцентные элементы (голубые как в GitHub)
    colors[ImGuiCol_Header] = ImVec4(0.24f, 0.56f, 0.98f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.74f, 0.76f, 0.76f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.24f, 0.56f, 0.98f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.24f, 0.56f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.56f, 0.98f, 0.78f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.24f, 0.56f, 0.98f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.0f);

    // Скроллбар
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);

    // Разное
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.56f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.56f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.24f, 0.56f, 0.98f, 0.95f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.24f, 0.56f, 0.98f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.24f, 0.56f, 0.98f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.24f, 0.56f, 0.98f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.24f, 0.56f, 0.98f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.56f, 0.98f, 0.35f);

    // Настройки стиля
    style->FrameBorderSize = 1;
    style->WindowRounding = 10;
    style->FrameRounding = 10;
    style->GrabRounding = 10;
    style->GrabMinSize = 20;
}
#pragma once
namespace ImGui {
    bool CustomToggle(const char* label, bool* v) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImGui::PushID(label);
        ImGui::TextColored((*v ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)), label);
        ImGui::SameLine();
        float height = ImGui::GetFrameHeight();
        float width = height * 1.55f;
        ImGuiStyle& style = ImGui::GetStyle();

        ImVec2 p = ImGui::GetCursorScreenPos();

        // Colors
        ImU32 color_bg_on = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImU32 color_bg_off = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImU32 color_knob = *v ? ImGui::GetColorU32(ImVec4(0.98f, 0.08f, 0.5f, 1.0f)) :
            ImGui::GetColorU32(ImVec4(0.36f, 0.36f, 0.36f, 1.0f));
        ImU32 glow_color = ImGui::GetColorU32(ImVec4(0.98f, 0.08f, 0.5f, 1.0f)); // Цвет свечения f80850
        ImU32 border_color = ImGui::GetColorU32(ImGuiCol_Border);

        ImGui::InvisibleButton(label, ImVec2(width, height));
        bool clicked = ImGui::IsItemClicked();
        if (clicked) *v = !(*v);

        // Background + Border
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), *v ? color_bg_on : color_bg_off, height);

        if (style.FrameBorderSize > 0.0f) {
            draw_list->AddRect(
                p,
                ImVec2(p.x + width, p.y + height),
                border_color,
                height * 0.5f,
                0,
                style.FrameBorderSize
            );
        }

        // Knob parameters
        float base_radius = *v ? 10 : 8;
        ImVec2 knob_pos = *v ?
            ImVec2(p.x + width - height * 0.5f, p.y + height * 0.5f) :
            ImVec2(p.x + height * 0.5f, p.y + height * 0.5f);

        // Glow effect (only when active)
        if (*v) {
            // Рисуем несколько слоев для эффекта свечения
            const int glow_layers = 3;
            for (int i = 0; i < glow_layers; i++) {
                float alpha = 0.3f * (1.0f - (float)i / glow_layers);
                float radius = base_radius + 2.0f * (i + 1);
                draw_list->AddCircle(
                    knob_pos,
                    radius,
                    ImGui::GetColorU32(ImVec4(0.98f, 0.08f, 0.5f, alpha)),
                    0, // сегменты (0 = автоматически)
                    2.0f // толщина линии
                );
            }
        }

        // Main knob
        draw_list->AddCircleFilled(knob_pos, base_radius, color_knob);

        ImGui::PopID();
        return clicked;
    }
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
    bool SliderInt64(const char* label, int64_t* v, int64_t v_min, int64_t v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalar(label, ImGuiDataType_S64, v, &v_min, &v_max, format, flags);
    }
    int64_t TextToCenter(const char* text) {
        int64_t iTextSizeX = ImGui::CalcTextSize(text).x;
        int64_t iTextSizeY = ImGui::CalcTextSize(text).y;
        int64_t iCurrentWindowSizeX = ImGui::GetWindowWidth();
        int64_t iCurrentWindowSizeY = ImGui::GetWindowHeight();
        ImGui::SetCursorPos(ImVec2((iCurrentWindowSizeX - iTextSizeX) / 2, (iCurrentWindowSizeY - iTextSizeY) / 2));
        return 0;
    }
    int64_t TextToCenterX(const char* text) {
        int64_t iTextSizeX = ImGui::CalcTextSize(text).x;
        int64_t iCurrentWindowSizeX = ImGui::GetWindowWidth();
        ImGui::SetCursorPosX((iCurrentWindowSizeX - iTextSizeX) / 2);
        return 0;
    }
    int64_t ItemToCenterX(int64_t sizeX) {
        int64_t iCurrentWindowSizeX = ImGui::GetWindowWidth();
        ImGui::SetCursorPosX((iCurrentWindowSizeX - sizeX) / 2);
        return 0;
    }
    int64_t ItemToCenterY(int64_t sizeY) {
        int64_t iCurrentWindowSizeY = ImGui::GetWindowHeight();
        ImGui::SetCursorPosY((iCurrentWindowSizeY - sizeY) / 2);
        return 0;
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
// Simple helper function to load an image into a Vulkan texture with common settings
auto sInfo = std::make_unique<PerfomanceData>();
auto mInfo = std::make_unique<MemoryData>();
auto ByteTransfer = std::make_unique<strData>();
auto CPU = std::make_unique<cpudata>();
//
std::string strArray;

//fA_int2str(sInfo->CommitLimit,&strArray);
//
//..
float64_t g = 0;
static std::string fCommitLimit = std::to_string((int64_t)sInfo->CommitLimit) + " Bytes";
static std::string fCommitPeak = std::to_string((int64_t)sInfo->CommitPeak) + " Bytes";
static std::string fCommitTotal = std::to_string((int64_t)sInfo->CommitTotal) + " Bytes";
static std::string fKernelNonpaged = std::to_string((int64_t)sInfo->KernelNonpaged) + " Bytes";
static std::string fKernelPaged = std::to_string((int64_t)sInfo->KernelPaged) + " Bytes";
static std::string fKernelTotal = std::to_string((int64_t)sInfo->KernelTotal) + " Bytes";
static std::string fPageSize = std::to_string((int64_t)sInfo->PageSize) + " Bytes";
static std::string fPhysicalAvailable = std::to_string((int64_t)sInfo->PhysicalAvailable) + " Bytes";
static std::string fPhysicalTotal = std::to_string((int64_t)sInfo->PhysicalTotal) + " Bytes";
static std::string fProcessCount = std::to_string(sInfo->ProcessCount);
static std::string fSystemCache = std::to_string((int64_t)sInfo->SystemCache) + " Bytes";
static std::string fThreadCount = std::to_string(sInfo->ThreadCount);
// 
static std::string fdwLenA = std::to_string((int64_t)mInfo->dwLenA);
static std::string fdwMemoryLoad = (std::to_string((int64_t)mInfo->dwMemoryLoad) + "%%").c_str();
static std::string fGBMemoryLoad = std::to_string(fMemStatus(7) - fMemStatus(4)) + " GB";
static std::string fullAvailExtendedVirtual = std::to_string((int64_t)mInfo->ullAvailExtendedVirtual) + " GB";
static std::string fullAvailPageFile = std::to_string((int64_t)sInfo->CommitLimit - (int64_t)sInfo->CommitTotal) + "GB";
static std::string fullAvailPhys = std::to_string((int64_t)mInfo->ullAvailPhys) + "GB";
static std::string fullAvailVirtual = std::to_string((int64_t)mInfo->ullAvailVirtual) + "GB";
static std::string fullTotalPageFile = std::to_string((int64_t)mInfo->ullTotalPageFile) + "GB";
static std::string fullTotalPhys = std::to_string((int64_t)mInfo->ullTotalPhys) + "GB";
static std::string fullTotalVirtual = std::to_string((int64_t)mInfo->ullTotalVirtual) + "GB";
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
static int64_t fMallocMemoryOffset = 1000;
//static std::string fTime = (std::to_string(tInfo.Hour) + ":" + std::to_string(tInfo.Min) + ":" + std::to_string(tInfo.Sec));
// Data stored per platform window
// Volk headers
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
#define VOLK_IMPLEMENTATION
#include <volk.h>
#endif

//#define APP_USE_UNLIMITED_FRAME_RATE
#ifdef _DEBUG
#define APP_USE_VULKAN_DEBUG_REPORT
#endif

// Data
static VkAllocationCallbacks* g_Allocator = nullptr;
static VkInstance               g_Instance = VK_NULL_HANDLE;
static VkPhysicalDevice         g_PhysicalDevice = VK_NULL_HANDLE;
static VkDevice                 g_Device = VK_NULL_HANDLE;
static uint32_t                 g_QueueFamily = (uint32_t)-1;
static VkQueue                  g_Queue = VK_NULL_HANDLE;
static VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
static VkPipelineCache          g_PipelineCache = VK_NULL_HANDLE;
static VkDescriptorPool         g_DescriptorPool = VK_NULL_HANDLE;

static ImGui_ImplVulkanH_Window g_MainWindowData;
static uint32_t                 g_MinImageCount = 2;
static bool                     g_SwapChainRebuild = false;
//


static void check_vk_result(VkResult err)
{
    if (err == VK_SUCCESS)
        return;
    fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
    if (err < 0)
        abort();
}

#ifdef APP_USE_VULKAN_DEBUG_REPORT
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
    (void)flags; (void)object; (void)location; (void)messageCode; (void)pUserData; (void)pLayerPrefix; // Unused arguments
    fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
    return VK_FALSE;
}
#endif // APP_USE_VULKAN_DEBUG_REPORT

static bool IsExtensionAvailable(const ImVector<VkExtensionProperties>& properties, const char* extension)
{
    for (const VkExtensionProperties& p : properties)
        if (strcmp(p.extensionName, extension) == 0)
            return true;
    return false;
}

static void SetupVulkan(ImVector<const char*> instance_extensions)
{
    VkResult err;
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
    volkInitialize();
#endif

    // Create Vulkan Instance
    {
        VkInstanceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        // Enumerate available extensions
        uint32_t properties_count;
        ImVector<VkExtensionProperties> properties;
        vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, nullptr);
        properties.resize(properties_count);
        err = vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, properties.Data);
        check_vk_result(err);

        // Enable required extensions
        if (IsExtensionAvailable(properties, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
            instance_extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
        if (IsExtensionAvailable(properties, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME))
        {
            instance_extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
            create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        }
#endif

        // Enabling validation layers
#ifdef APP_USE_VULKAN_DEBUG_REPORT
        const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
        create_info.enabledLayerCount = 1;
        create_info.ppEnabledLayerNames = layers;
        instance_extensions.push_back("VK_EXT_debug_report");
#endif

        // Create Vulkan Instance
        create_info.enabledExtensionCount = (uint32_t)instance_extensions.Size;
        create_info.ppEnabledExtensionNames = instance_extensions.Data;
        err = vkCreateInstance(&create_info, g_Allocator, &g_Instance);
        check_vk_result(err);
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
        volkLoadInstance(g_Instance);
#endif

        // Setup the debug report callback
#ifdef APP_USE_VULKAN_DEBUG_REPORT
        auto f_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(g_Instance, "vkCreateDebugReportCallbackEXT");
        IM_ASSERT(f_vkCreateDebugReportCallbackEXT != nullptr);
        VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
        debug_report_ci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        debug_report_ci.pfnCallback = debug_report;
        debug_report_ci.pUserData = nullptr;
        err = f_vkCreateDebugReportCallbackEXT(g_Instance, &debug_report_ci, g_Allocator, &g_DebugReport);
        check_vk_result(err);
#endif
    }

    // Select Physical Device (GPU)
    uint32_t gpu_count = 0;
    vkEnumeratePhysicalDevices(g_Instance, &gpu_count, nullptr);
    IM_ASSERT(gpu_count > 0);
    std::vector<VkPhysicalDevice> gpus(gpu_count);
    vkEnumeratePhysicalDevices(g_Instance, &gpu_count, gpus.data());
    g_PhysicalDevice = gpus[0];

    // Select graphics queue family
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &queue_family_count, queue_families.data());

    for (uint32_t i = 0; i < queue_family_count; i++) {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            g_QueueFamily = i;
            break;
        }
    }
    IM_ASSERT(g_QueueFamily != (uint32_t)-1);

    // Create Logical Device (with 1 queue)
    {
        ImVector<const char*> device_extensions;
        device_extensions.push_back("VK_KHR_swapchain");

        // Enumerate physical device extension
        uint32_t properties_count;
        ImVector<VkExtensionProperties> properties;
        vkEnumerateDeviceExtensionProperties(g_PhysicalDevice, nullptr, &properties_count, nullptr);
        properties.resize(properties_count);
        vkEnumerateDeviceExtensionProperties(g_PhysicalDevice, nullptr, &properties_count, properties.Data);
#ifdef VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME
        if (IsExtensionAvailable(properties, VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME))
            device_extensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
#endif

        const float queue_priority[] = { 1.0f };
        VkDeviceQueueCreateInfo queue_info[1] = {};
        queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_info[0].queueFamilyIndex = g_QueueFamily;
        queue_info[0].queueCount = 1;
        queue_info[0].pQueuePriorities = queue_priority;
        VkDeviceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
        create_info.pQueueCreateInfos = queue_info;
        create_info.enabledExtensionCount = (uint32_t)device_extensions.Size;
        create_info.ppEnabledExtensionNames = device_extensions.Data;
        err = vkCreateDevice(g_PhysicalDevice, &create_info, g_Allocator, &g_Device);
        check_vk_result(err);
        vkGetDeviceQueue(g_Device, g_QueueFamily, 0, &g_Queue);
    }

    // Create Descriptor Pool
    // If you wish to load e.g. additional textures you may need to alter pools sizes and maxSets.
    {
        {
            // Минимальные требования для ImGui
            VkDescriptorPoolSize pool_sizes[] = {
                { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 }
            };

            VkDescriptorPoolCreateInfo pool_info = {};
            pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
            pool_info.maxSets = 1000;  // Должно быть ≥ общего количества дескрипторов
            pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
            pool_info.pPoolSizes = pool_sizes;

            VkResult err = vkCreateDescriptorPool(g_Device, &pool_info, g_Allocator, &g_DescriptorPool);
            if (err != VK_SUCCESS) {
                fprintf(stderr, "Failed to create descriptor pool (Error: %d)\n", err);
                
            }
        }
    }
}

// All the ImGui_ImplVulkanH_XXX structures/functions are optional helpers used by the demo.
// Your real engine/app may not use them.
static void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height)
{
    wd->Surface = surface;

    // Check for WSI support
    VkBool32 res;
    vkGetPhysicalDeviceSurfaceSupportKHR(g_PhysicalDevice, g_QueueFamily, wd->Surface, &res);
    if (res != VK_TRUE)
    {
        fprintf(stderr, "Error no WSI support on physical device 0\n");
        exit(-1);
    }

    // Select Surface Format
    const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
    const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(g_PhysicalDevice, wd->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

    // Select Present Mode
#ifdef APP_USE_UNLIMITED_FRAME_RATE
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
#else
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
    wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(g_PhysicalDevice, wd->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));
    //printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

    // Create SwapChain, RenderPass, Framebuffer, etc.
    IM_ASSERT(g_MinImageCount >= 2);
    ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, wd, g_QueueFamily, g_Allocator, width, height, g_MinImageCount);
}

static void CleanupVulkan()
{
    vkDestroyDescriptorPool(g_Device, g_DescriptorPool, g_Allocator);

#ifdef APP_USE_VULKAN_DEBUG_REPORT
    // Remove the debug report callback
    auto f_vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(g_Instance, "vkDestroyDebugReportCallbackEXT");
    f_vkDestroyDebugReportCallbackEXT(g_Instance, g_DebugReport, g_Allocator);
#endif // APP_USE_VULKAN_DEBUG_REPORT

    vkDestroyDevice(g_Device, g_Allocator);
    vkDestroyInstance(g_Instance, g_Allocator);
}

static void CleanupVulkanWindow()
{
    ImGui_ImplVulkanH_DestroyWindow(g_Instance, g_Device, &g_MainWindowData, g_Allocator);
}

static void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data)
{
    VkSemaphore image_acquired_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    VkResult err = vkAcquireNextImageKHR(g_Device, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
        g_SwapChainRebuild = true;
    if (err == VK_ERROR_OUT_OF_DATE_KHR)
        return;
    if (err != VK_SUBOPTIMAL_KHR)
        check_vk_result(err);

    ImGui_ImplVulkanH_Frame* fd = &wd->Frames[wd->FrameIndex];
    {
        err = vkWaitForFences(g_Device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
        check_vk_result(err);

        err = vkResetFences(g_Device, 1, &fd->Fence);
        check_vk_result(err);
    }
    {
        err = vkResetCommandPool(g_Device, fd->CommandPool, 0);
        check_vk_result(err);
        VkCommandBufferBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
        check_vk_result(err);
    }
    {
        VkRenderPassBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        info.renderPass = wd->RenderPass;
        info.framebuffer = fd->Framebuffer;
        info.renderArea.extent.width = wd->Width;
        info.renderArea.extent.height = wd->Height;
        info.clearValueCount = 1;
        info.pClearValues = &wd->ClearValue;
        vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
    }

    // Record dear imgui primitives into command buffer
    ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

    // Submit command buffer
    vkCmdEndRenderPass(fd->CommandBuffer);
    {
        VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        VkSubmitInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &image_acquired_semaphore;
        info.pWaitDstStageMask = &wait_stage;
        info.commandBufferCount = 1;
        info.pCommandBuffers = &fd->CommandBuffer;
        info.signalSemaphoreCount = 1;
        info.pSignalSemaphores = &render_complete_semaphore;

        err = vkEndCommandBuffer(fd->CommandBuffer);
        check_vk_result(err);
        err = vkQueueSubmit(g_Queue, 1, &info, fd->Fence);
        check_vk_result(err);
    }
}

static void FramePresent(ImGui_ImplVulkanH_Window* wd)
{
    if (g_SwapChainRebuild)
        return;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    VkPresentInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.waitSemaphoreCount = 1;
    info.pWaitSemaphores = &render_complete_semaphore;
    info.swapchainCount = 1;
    info.pSwapchains = &wd->Swapchain;
    info.pImageIndices = &wd->FrameIndex;
    VkResult err = vkQueuePresentKHR(g_Queue, &info);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
        g_SwapChainRebuild = true;
    if (err == VK_ERROR_OUT_OF_DATE_KHR)
        return;
    if (err != VK_SUBOPTIMAL_KHR)
        check_vk_result(err);
    wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->SemaphoreCount; // Now we can use the next set of semaphores
}
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void ReloadData() {
    fdwLenA = std::to_string((int64_t)mInfo->dwLenA);
    fdwMemoryLoad = (std::to_string((int64_t)mInfo->dwMemoryLoad) + "%%").c_str();
    fGBMemoryLoad = std::to_string(fMemStatus(7) - fMemStatus(4)) + " GB";
    fullTotalPhys = std::to_string((int64_t)mInfo->ullTotalPhys) + "GB";
    CPU->fcpu_data = GetProcessorSpeed();
    CPU->fNUMANodes = std::to_string(dDataCPU(1));
    CPU->fPhysNumberPackages = std::to_string(dDataCPU(2));
    CPU->fCPUCores = std::to_string(dDataCPU(3));
    CPU->fCPULogicalCores = std::to_string(dDataCPU(4));
    CPU->fCPULoadPercent;
    CPU->fCPUSpeed = std::to_string(CPU->fcpu_data) + " Mhz";
}

static bool ImMessageBox(std::string text, std::string title, int64_t style) {
    ImGui::OpenPopup((title).c_str());
    if (ImGui::BeginPopupModal((title).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("SYSTEM-Z");
        ImGui::Separator();
        ImGui::Text((text).c_str());
        if (style) {
            if (ImGui::Button("OK", ImVec2(120, 0))) {
                return true;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                return false;
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }
}
static void ClearStacks() {
    std::default_delete<PerfomanceData>;
    std::default_delete<MemoryData>;
    std::default_delete<strData>;
    std::default_delete<cpudata>;
    std::default_delete<AMD_GPU>;
}
static void DarkStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 1.0f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.53f, 0.53f, 0.53f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 0.00f, 0.50f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 0.0f);
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
    style.FrameBorderSize = 1;
}
std::string vkGetDeviceType(int64_t vkDeviceId) {
    /* VK_PHYSICAL_DEVICE_TYPE_OTHER = 0,
         VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU = 1,
         VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU = 2,
         VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU = 3,
         VK_PHYSICAL_DEVICE_TYPE_CPU = 4,
         VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM = 0x7FFFFFFF*/
    static std::string vkDeviceString;
    switch (vkDeviceId) {
    case 0:
        vkDeviceString = "other GPU";
        break;
    case 1:
        vkDeviceString = "Integrated GPU";
        break;
    case 2:
        vkDeviceString = "Discrete GPU";
        break;
    case 3:
        vkDeviceString = "Virtual GPU";
        break;
    case 4:
        vkDeviceString = "CPU";
        break;
    }
    return vkDeviceString;

}
class GPU_DATA {
public:
    std::string vkBrand = "";
    std::string vkModel = "";
    struct { uint32_t x, y, z, w; } VulkanAPIVer;
    std::string vkDeviceType = "";
    void vkGetVer(VkPhysicalDeviceProperties* dp);
private:
    std::string apiVer = "";
};
void GPU_DATA::vkGetVer(VkPhysicalDeviceProperties *dp) {

    // 4. Извлечение версии Vulkan
    uint32_t major_version = VK_VERSION_MAJOR(dp->apiVersion);
    uint32_t minor_version = VK_VERSION_MINOR(dp->apiVersion);
    uint32_t patch_version = VK_VERSION_PATCH(dp->apiVersion);

    //apiVer = std::to_string(major_version) + "." + std::to_string(minor_version) + "." + std::to_string(patch_version);
    VulkanAPIVer.x = major_version;
    VulkanAPIVer.y = minor_version;
    VulkanAPIVer.z = patch_version;
    VulkanAPIVer.w = dp->apiVersion;
}
int main(int, char** argv)
{
    ImVec4 clear_color(0, 0,0, 1);
    // AGPU->agsCheck();
     //ByteTransfer->int2str(123, &strArray);
    ByteTransfer->int642str(13, &strArray);
    g = 1, 3333;
    double64_t d;
    std::cout << "Test double64_t size:" << sizeof(d) << "data_test:" << g << std::endl;
    ImDrawListSplitter JEApp;
    char fInputBuffer;
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"SYSTEM-Z_AMDVulkan_1.3_(1.2.4.1ffe_amd64)_AMD_GPU", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"SYSTEM-Z_AMDVulkan_1.3(1.2.4.1ffe_amd64)_AMD_GPU", WS_OVERLAPPEDWINDOW | WS_EX_TOOLWINDOW | WS_EX_NOPARENTNOTIFY, 100, 80, 590, 830, nullptr, nullptr, wc.hInstance, nullptr);
    ::SetWindowLongA(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
    ImVector<const char*> extensions;
    extensions.push_back("VK_KHR_surface");
    extensions.push_back("VK_KHR_win32_surface");
    SetupVulkan(extensions);
    
    // Create Window Surface
    VkSurfaceKHR surface;
    VkResult err;
    VkWin32SurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = hwnd;
    createInfo.hinstance = ::GetModuleHandle(nullptr);
    if (vkCreateWin32SurfaceKHR(g_Instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
    {
        printf("Failed to create Vulkan surface.\n");
        return 1;
    }

    // Show the window
    // FIXME: Retrieve client size from window itself.
    
    struct LOGO {
        GLuint logoBuffer;
        int lcx = 0;
        int lcy = 0;
        uint8_t u8Buffer;
    };
    GPU_DATA* GPU = new GPU_DATA;
    ImGui_ImplVulkanH_Window* wd = &g_MainWindowData;
    SetupVulkanWindow(wd, surface, 1280, 800);
    auto props = std::make_unique<VkPhysicalDeviceProperties>();
    vkGetPhysicalDeviceProperties(g_PhysicalDevice, props.get()); // Используем .get()

    printf("Using GPU: %s\n", props->deviceName);
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    ::ShowWindow(GetConsoleWindow(), 2);
    ::UpdateWindow(hwnd);
    std::string fStrParam;
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    VkSamplerCreateInfo sampler_info = {};
    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_info.magFilter = VK_FILTER_LINEAR;
    sampler_info.minFilter = VK_FILTER_LINEAR;
    sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.minLod = -1000;
    sampler_info.maxLod = 1000;
    sampler_info.maxAnisotropy = 1.0f;

    VkSampler sampler;
    if (vkCreateSampler(g_Device, &sampler_info, nullptr, &sampler) != VK_SUCCESS) {
        // Обработка ошибки
    }
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    // Убедитесь, что RenderPass установлен перед инициализацией ImGui Vulkan
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = g_Instance;
    init_info.PhysicalDevice = g_PhysicalDevice;
    init_info.Device = g_Device;
    init_info.QueueFamily = g_QueueFamily;
    init_info.Queue = g_Queue;
    init_info.PipelineCache = g_PipelineCache;
    init_info.DescriptorPool = g_DescriptorPool;
    init_info.RenderPass = wd->RenderPass;  // Это критически важно!
    init_info.Subpass = 0;
    init_info.MinImageCount = g_MinImageCount;
    init_info.ImageCount = wd->ImageCount;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.Allocator = g_Allocator;
    init_info.CheckVkResultFn = check_vk_result;

    if (!ImGui_ImplVulkan_Init(&init_info)) {
        fprintf(stderr, "Failed to initialize ImGui Vulkan!\n");
        exit(1);
    }
    CVk->Init(g_Device, g_PhysicalDevice, g_Queue, VkGetCommandPool(g_Device, g_QueueFamily));
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(g_PhysicalDevice, &features);
    if (!features.geometryShader) {
        fprintf(stderr, "Geometry shaders not supported!\n");
        exit(1);
    }
    io.Fonts->AddFontFromFileTTF(".\\SFMono-Bold.ttf", 18.0f);//
    ImFont* font40 = io.Fonts->AddFontFromFileTTF(".\\SFMono-Bold.ttf", 30.0f);
    ImFont* font60 = io.Fonts->AddFontFromFileTTF(".\\SFMono-Bold.ttf", 50.0f);
    //SetColorAMD64(240);
    auto driveInfoNavigator = std::make_unique<DriveInfoNavigator>();
    // std::cout << "" << "Vulkan Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
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
    // Main loop\
            //struct TimeOffset {
    int64_t Hour = fLTime(0);
    int64_t Min = fLTime(1);
    int64_t Sec = fLTime(2);
    bool main_logo = true;
    bool done = false;
    std::string you_cpu_brand;
    for (int b = 0; b < 3; b++) {
        you_cpu_brand += dCPUBrandString[b];
    }
    std::string you_gpu_brand;
    for (int b = 0; b < 3; b++) {
        you_gpu_brand += GPU->vkBrand[b];
    }
    auto AGPULogo = std::make_unique<LOGO>();
    DarkStyle();

    // Загрузка текстуры
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    int width; int height;
    VkImage textureImage2;
    VkDeviceMemory textureImageMemory2;
    VkImageView textureImageView2;
    int width2; int height2;
    // Использование в дескрипторе (пример)
    VkDescriptorImageInfo imageInfo;
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureImageView;
    imageInfo.sampler = sampler; // Вам также понадобится создать сэмплер
    if (!CVk->LoadImageToMemory("HCPP_STUDIO_LOGO.png", &textureImage, &textureImageView,
        &width, &height, &textureImageMemory)) {
        MessageBoxA(AGPU->hwnd, "[vulkan] Fatal: Error Load Texture to VideoMemory! ", "SYSTEM-Z::VulkanExceptions", 1);
    }
    VkDescriptorSet desc_set = ImGui_ImplVulkan_AddTexture(
        sampler,                  // Ваш сэмплер
        textureImageView,         // ImageView для текстуры
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL // Правильный layout
    );
    if (!CVk->LoadImageToMemory("back.jpg", &textureImage2, &textureImageView2,
        &width2, &height2, &textureImageMemory2)) {
        MessageBoxA(AGPU->hwnd, "[vulkan] Fatal: Error Load Texture to VideoMemory! ", "SYSTEM-Z::VulkanExceptions", 1);
    }
    VkDescriptorSet desc_set2 = ImGui_ImplVulkan_AddTexture(
        sampler,                  // Ваш сэмплер
        textureImageView2,         // ImageView для текстуры
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL // Правильный layout
    );
  //  CGL->LoadImageToMemory("HCPP_STUDIO_LOGO.png",&AGPULogo->logoBuffer, &AGPULogo->lcx, &AGPULogo->lcy, &AGPULogo->u8Buffer);
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
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        
            static bool bColorSwitch = true;
           //bColorSwitch = ImMessageBox("Select Style Dark?", "SYSTEM-Z::Theme", 1);
            bool fJEFrame = true;
            char intBuffer;
            JEApp.ClearFreeMemory();

        

       static bool b_vsync = true;
        if (argv[1] == "vsync=true") {
            b_vsync = true;
        }
        if (argv[1] == "vsync=false") {
            b_vsync = true;
        }

        // };
        //uint64_t *stack_ptr = nullptr;
        SetWindowTextA(AGPU->hwnd, std::string("SYSTEM-Z_Vulkan_(1.2.4.1ffe_amd64)_AMD_GPU::mem:" + std::to_string(((fDataMemUsage() / 1024) / 1024)) + " MB").c_str());
        //std::cout << "[INFO] Malloc Memory to stack:" << std::to_string((fMallocMemoryOffset * 8) +((fDataMemUsage() / 1024) / 1024)) << "MB"<<" [BufferPtr::stack:"<<&stack_ptr<<"][block_size:"<<sizeof(stack_ptr)<<"*"<< fMallocMemoryOffset <<"]" << std::endl;
         //TimeOffset tInfo;
        static std::string fTime = (std::to_string(Hour) + ":" + std::to_string(Min) + ":" + std::to_string(Sec));
        JEApp.ClearFreeMemory();
        if (b_vsync) {
            Sleep(13);
            // WriteConfigJE << "fJEVsync=true;" << std::endl;
        }
        bool bSwitchBool = true;
        static  bool loadingWindow = false;
        static int64_t uLoad = 0;
        static int64_t uLexit = 0;
        static uint64_t ldColorSpinner = 0;
        static bool exitWindow = false;
        static bool fS_rtMetrics = false;
        static bool fM_rt = false;
        static int64_t perUpdate = 0;
        static bool bCPU_Bench = false;
        static bool hashGenStart = false;
        static double endHashTime2;
        static bool bMemoryBench;
        ImU32 col = 0;

        DarkStyle();
        static bool bSystem_zFrame = false;
        if (bSwitchBool) {
            ImGui::Begin("Image", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
            ImGui::SetWindowPos(ImVec2(-7, -5));
            ImGui::SetWindowSize(ImVec2(600, 800));
            ImGui::Image((ImTextureID)desc_set2, ImVec2(600,800));
            ImGui::End();
            if (main_logo) {
                GPU->vkBrand = (const char*)props->deviceName;
                GPU->vkDeviceType = vkGetDeviceType(props->deviceType);
                // ConsolePut("INFO: Main Frame Open");
                JEApp.ClearFreeMemory();
                ImGui::Begin("LOGO", &main_logo, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
                // CurrentWindowSizeW(AGPU->hwnd, &AGPU->wx, &AGPU->wy);
                ImGui::SetWindowSize(ImVec2(AGPU->wx, AGPU->wy));
                static std::string fGlichText;
                AGPU->SYSTEM_Z(&fGlichText);

                ImGui::SetWindowPos(ImVec2(-2, 1));
                ImGui::SetCursorPos(ImVec2(103, 179));
                ImGui::PushFont(font60);
                ImGui::TextToCenterX("SYSTEM-Z 1.2");
                ImGui::Text((fGlichText).c_str());
                ImGui::PopFont();
                if (!loadingWindow) {
                    if (!exitWindow)
                    {
                        ImGui::ItemToCenterX(256); ImGui::SetCursorPosY(-16);
                     ImGui::Image((ImTextureID)desc_set, ImVec2(256, 256)); ImGui::SetCursorPosY(256); ImGui::TextToCenterX("used AMD_AGS_x64 (C++20) (Work Only AMD GPU)"); ImGui::Text(" HCPP STUDIO. Program to GNU License\nused AMD_AGS_x64 (C++20) (Work Only AMD GPU)\n(Full GPU Info only AMD GPU)\nWrittein to C++20 x64 MSVC(GCC)");
                        // ConsolePut("INFO: Loading no Open");HCPP_STUDIO_LOGO.png
                        ImGui::ItemToCenterX(250);
                        if (ImGui::Button("START", ImVec2(250.0f, 30.0f))) {
                            AGPU->agsCheck(); loadingWindow = true;
                            dumpMemory << Hour << ":"<<Min<<":"<<Sec << " INFO:" << AGPU->GPUInitMsg << std::endl;
                          //  loadingWindow = true;
                        }
                    }
                }
                if (exitWindow) {
                  //  AGPU->agsShutdown();
                    //ConsolePut("INFO: Exiting");
                    col = ImGui::GetColorU32(ImVec4(1.0f, 0, 0.60f, 1.0f));
                    loadingWindow = false;
                    main_logo = true;
                    uLexit++;
                    ImGui::PushFont(font60);
                    ImGui::TextToCenterX("Exiting..");
                    ImGui::Text("Exiting..");
                    ImGui::PopFont();
                    ImGui::SetCursorPos(ImVec2(123, 269));
                   // ImGui::Text("%s stack=%p",AGPU->GPUInitMsg,&AGPU);
                    ImGui::ItemToCenterX(20);
                    ImGui::Spinner("Please wait..", 20, 4, col);
                    if (uLexit == 100) {
                        if (AGPU->fAGSState) {
                            ClearStacks();
                            exit(0);
                        }
                    }
                }
                if (loadingWindow) {
                        col = ImGui::GetColorU32(ImVec4(1.0f, 0, 0.60f, 1.0f));
                    // ConsolePut("INFO: Loading Open");
                    uLoad++;
                    ImGui::SetCursorPos(ImVec2(133, 269));
                   // ImGui::Text((AGPU->GPUInitMsg + "\n%p->%d").c_str(), &AGPU,sizeof(AGPU));
                    loadingWindow = ImMessageBox(AGPU->GPUInitMsg, "SYSTEM-Z::AMD_GPU", 0);
                    ImGui::SetCursorPos(ImVec2(233, 340));
                    ImGui::Spinner("Loading data", 20, 4, col);
                    if (uLoad == 100) {
                        main_logo = false;
                        loadingWindow = false;
                        bSystem_zFrame = true;
                    }
                }
               
                ImGui::End();
            }
            if (!main_logo) {
                ImGui::Begin("Main Info", &bSystem_zFrame, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
                main_logo = false;

                JEApp.ClearFreeMemory();
                ImGui::SetWindowSize(ImVec2(AGPU->wx, AGPU->wy));
                perUpdate++;
                if (perUpdate >= 100) {
                    if (fM_rt) { ReloadData(); };
                    perUpdate = 0;
                }
                if (exitWindow) {
                    //  AGPU->agsShutdown();
                      //ConsolePut("INFO: Exiting");
                    col = ImGui::GetColorU32(ImVec4(1.0f, 0, 0.60f, 1.0f));
                    loadingWindow = false;
                    main_logo = true;
                    uLexit++;
                    ImGui::PushFont(font60);
                    ImGui::TextToCenterX("Exiting..");
                    ImGui::Text("Exiting..");
                    ImGui::PopFont();
                    ImGui::SetCursorPos(ImVec2(123, 269));
                    // ImGui::Text("%s stack=%p",AGPU->GPUInitMsg,&AGPU);
                    ImGui::ItemToCenterX(20);
                    ImGui::Spinner("Please wait..", 20, 4, col);
                    if (uLexit == 100) {
                        if (AGPU->fAGSState) {
                            ClearStacks();
                            exit(0);
                        }
                    }
                }
                if (loadingWindow) {
                    col = ImGui::GetColorU32(ImVec4(1.0f, 0, 0.60f, 1.0f));
                    // ConsolePut("INFO: Loading Open");
                    uLoad++;
                    ImGui::SetCursorPos(ImVec2(133, 269));
                    // ImGui::Text((AGPU->GPUInitMsg + "\n%p->%d").c_str(), &AGPU,sizeof(AGPU));
                    loadingWindow = ImMessageBox(AGPU->GPUInitMsg, "SYSTEM-Z::AMD_GPU", 0);
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
                static bool fS_rtMetrics = false;
                static bool fM_rt = false;
                static int64_t perUpdate = 0;
                loadingWindow = false;
                JEApp.ClearFreeMemory();
                ImGui::Begin("Main Info", &main_logo, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
                
                perUpdate++;
                if (perUpdate >= 100) {
                    if (fM_rt) { ReloadData(); };
                    perUpdate = 0;
                }
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
                    ImGui::OpenPopup("SYSTEM-Z::Memory");
                }
                ImGui::SameLine();
                if (ImGui::Button("CPU Bench", ImVec2(150.0f, 30.0f))) {
                    hashGenStart = true; if (b_vsync) { b_vsync = false; }
                }
                ImGui::Separator();
                ImGui::CustomToggle("60HZ", &b_vsync); ImGui::SameLine(); ImGui::CustomToggle("SHOW FPS:", &fS_rtMetrics); ImGui::SameLine(); ImGui::CustomToggle(std::string(fM_rt ? "RTM: ON " : "RTM: OFF").c_str(), &fM_rt); ImGui::SameLine();  ImGui::TextColored(ImVec4(1, 0, .40f, 1), "(select theme Press [S]");
                ImGui::Separator();
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
                ImGui::Separator();
                ImGui::SeparatorText("CPU Hash Bench");
                if (hashGenStart) {
                    dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "Started CPU Bench" << " chunk_size:" << 3000000 << std::endl;
                    //srand(time(0));
                    auto t0 = high_resolution_clock::now();
                   /* for (uint64_t chk = 0; chk <= 3000000; chk++) {
                        fM_strBuffer += fM_CharsBuffer[rand() % fM_CharsBuffer.size()];
                    }
                    */
                    GenHashToAllThreads();
                    auto t1 = high_resolution_clock::now();
                    double endHashTime = duration_cast<milliseconds>(t1 - t0).count();
                    dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "Stoped CPU Bench" << " time:" << endHashTime <<"ms" << std::endl;
                    endHashTime2 = endHashTime;
                    if (!b_vsync) { b_vsync = true; }
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
                if (you_cpu_brand == "AMD") {
                    you_cpu_brand = "AMD";
                }
                if (you_cpu_brand == "INT") {
                    you_cpu_brand = "Intel";
                }
                if (you_gpu_brand == "AMD") {
                    you_gpu_brand = "AMD";
                }
                if (you_gpu_brand == "INT") {
                    you_gpu_brand = "Intel";
                }
                if (you_gpu_brand == "Nvi") {
                    you_gpu_brand = "Nvidia";
                }
                Hour = fLTime(0);
                Min  = fLTime(1);
                Sec  = fLTime(2);
                //
                //vkGetVRAMUsage
                static bool bWVKExt = false;
                static  bool rs = true;
                if (bWVKExt) {
                    static uint32_t extensionCount = 0;
                    static std::vector<VkExtensionProperties> extensions;
                    static bool initialized = false;

                    if (!initialized) {
                        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
                        extensions.resize(extensionCount);
                        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
                        initialized = true;
                    }
                    if (ImGui::BeginPopupModal("Vulkan Extensions", &bWVKExt, ImGuiWindowFlags_AlwaysAutoResize)) {
                        ImGui::Text("Supported extensions: %d", extensionCount);
                        ImGui::Separator();
                        uint32_t index = 1;
                        for (const auto& extension : extensions) {
                            ImGui::Text("[vulkan] %d %s", index++, extension.extensionName);
                        }
                        ImGui::EndPopup();
                    }
                }
                if (ImGui::BeginPopupModal("Low Perfomance", &rs, ImGuiWindowFlags_AlwaysAutoResize)) {
                    ImGui::Text("Warning!!");
                    ImGui::Separator();
                    ImGui::Text("You device work to Slow!!");
                    ImGui::Text("Framerate: %.2f", io.Framerate);
                    ImGui::EndPopup();
                }
                vkGetVRAMUsage(init_info.PhysicalDevice, &AGPU->vkMemHeapSize, &AGPU->vkMemUsage);
                ImGui::SetWindowPos(ImVec2(-3, -2));
                ImGui::SeparatorText(("CPU INFO (" + you_cpu_brand + ")").c_str());
                ImGui::TextColored((you_cpu_brand == "AMD" ? ImVec4(1,0,0.60f,1) : ImVec4(0.30f,0,1.0f,1)),("CPU:" + dCPUBrandString).c_str()); ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), "CPU %s cores/ %s threads", CPU->fCPUCores, CPU->fCPULogicalCores);
                ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), ("NUMA Nodes:" + CPU->fNUMANodes).c_str()); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), " Base CPU Speed: %s", CPU->fCPUSpeed);
                ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), ("Physical CPU packages:" + CPU->fPhysNumberPackages).c_str()); 
                ImGui::SeparatorText(("GPU INFO (" + you_gpu_brand+")").c_str());
                ImGui::Text(("GPU:" + (GPU->vkBrand)).c_str()); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1, 0.50f, 1.0f), "%.2f GB", AGPU->GPUlocalMemory / 1024 / 1024 / 1024);
                ImGui::Text("Vulkan Extensions"); ImGui::SameLine();
                if (ImGui::Button("Show", ImVec2(100, 30))) {
                    bWVKExt = true; ImGui::OpenPopup("Vulkan Extensions");
                }
                GPU->vkGetVer(props.get());
                //std::cout << "raw ver" << GPU->VulkanAPIVer.w << GPU->VulkanAPIVer.x<<"." << GPU->VulkanAPIVer.y << "." << GPU->VulkanAPIVer.z << std::endl;
                ImGui::Text("GPU Type: %s", GPU->vkDeviceType); ImGui::SameLine(); ImGui::Text("[VulkanAPI]: %i.%i.%i", GPU->VulkanAPIVer.x, GPU->VulkanAPIVer.y, GPU->VulkanAPIVer.z);
                ImGui::Text("VRAM: %d / %d MB", AGPU->vkMemUsage, AGPU->vkMemHeapSize);
                if (!AGPU->GPUNotAMD) {
                    ImGui::Text("You GPU not Supported!! Error: gpuStack:%p", &gpuInfo.devices[gpuIndex]);
                }
                if (io.Framerate < 30) {
                    ImGui::OpenPopup("Low Perfomance");
                    rs = true;
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
                    fS_rtMetrics ?  ImGui::Text( " FPS:%.3f",io.Framerate) : ImGui::Text(" FPS: OFF");
                    ImGui::Columns(1);
                }
                ImGui::SeparatorText("HDD/SSD Info (fix crash https://github.com/Esewqe' )");
                ImGui::Text("Drives: %d", driveInfoNavigator->totalDrives);  ImGui::SameLine();
                ImGui::Text((driveInfoNavigator->selectedType).c_str()); ImGui::SameLine();
                ImGui::Text((driveInfoNavigator->selectedName).c_str()); ImGui::SameLine();
                ImGui::Text((driveInfoNavigator->selectedTotalSize + " / " + driveInfoNavigator->selectedFreeSpaceSize).c_str());;
                // ImGui::SameLine();

                if (ImGui::Button("<", ImVec2(30.0f, 30.0f))) {
                    driveInfoNavigator->Prev();
                    dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "Disk Selected:"<< driveInfoNavigator->selectedType<< driveInfoNavigator->selectedName<< driveInfoNavigator->selectedTotalSize + " / " + driveInfoNavigator->selectedFreeSpaceSize << std::endl;
                }

                ImGui::SameLine();

                if (ImGui::Button(">", ImVec2(30.0f, 30.0f))) {
                    driveInfoNavigator->Next();
                    dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "Disk Selected:" << driveInfoNavigator->selectedType << driveInfoNavigator->selectedName << driveInfoNavigator->selectedTotalSize + " / " + driveInfoNavigator->selectedFreeSpaceSize << std::endl;
                }

                // ImGui::Text(DiskData->msg);
                ImGui::SeparatorText("MEMORY INFO");
                ImGui::Text(("Memory Load:" + (fdwMemoryLoad)+"/" + fGBMemoryLoad).c_str()); ImGui::SameLine();
                ImGui::Text(("Free Memory:" + (fullAvailPhys)).c_str()); ImGui::SameLine();
                ImGui::Text(("Total Memory:" + (fullTotalPhys)).c_str());
                static int64_t i64v = 0;
                ImGui::SeparatorText("MEMORY BENCH (v1.2)");
                ImGui::SliderInt64(":", &fMallocMemoryOffset, 0, (mInfo->ullAvailPhys * 1024 / 8), "(%.2d * 8) MB", NULL); ImGui::SameLine();
                ImGui::Text((std::to_string(((fMallocMemoryOffset) * 8 / 1024 < 1) ? (fMallocMemoryOffset) * 8 : (fMallocMemoryOffset) * 8 / 1024) + ((fMallocMemoryOffset) * 8 / 1024 < 1 ? "MB/" : "/") + fullAvailPhys + " GB").c_str());
                if (((fMallocMemoryOffset) * 8 / 1024) >= mInfo->ullAvailPhys) {
                    fMallocMemoryOffset = ((mInfo->ullAvailPhys) * 1024 / 8);
                    i64v = ((mInfo->ullAvailPhys) * 1024 / 8);
                    ImGui::TextColored(ImVec4(1.0f, 0, 0.50f, 1), "Error!! not malloc memory to biggest you free ram!! %d/%s", ((fMallocMemoryOffset) * 8 / 1024), fullAvailPhys);
                }
                ImGui::Columns(2, "##BenchTests", true);
                ImGui::Text("Write test:");
                ImGui::Text("Time: %d ms", write_timeOut);
                ImGui::Text("Speed:%.2f GB/S", write_speedOut);
                ImGui::NextColumn();
                ImGui::Text("Read test:");
                ImGui::Text("Time:%d ms ", read_timeOut);
                ImGui::Text("Speed: %.2f GB/S", read_speedOut);
                ImGui::Columns(1);
                static bool bWindowHandle = true;
              /*  ImGui::BeginPopupModal("Memory_Test",&bWindowHandle, ImGuiWindowFlags_Popup);
                ImGui::Text("%s", ("[WARNING]The process cannot be stopped\nThe benchmark consumes " + std::string(std::to_string((fMallocMemoryOffset) * 8)) + " MB of RAM").c_str());
                    bWindowHandle = ImGui::Button("OK") ? true : false;
                    ImGui::SameLine();
                    bWindowHandle = ImGui::Button("Cancel") ? true : false;
                
                if (bWindowHandle) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();*/
                if (ImGui::BeginPopupModal("SYSTEM-Z::Memory", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    ImGui::Text("SYSTEM-Z");
                    ImGui::Separator();
                    ImGui::Text(("[WARNING]The process cannot be stopped\nThe benchmark consumes " + std::string(std::to_string((fMallocMemoryOffset) * 8)) + " MB of RAM").c_str());
                    if (ImGui::Button("OK", ImVec2(120, 0))) {
                        fCBenchMemory = true;
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::SameLine();
                    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }
                if (fCBenchMemory) {
                    dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "Memory Bench Started" << " stack_size:" << ((fMallocMemoryOffset) * 8) / 1024 << std::endl;

                   // ImMessageBox(("[WARNING]The process cannot be stopped\nThe benchmark consumes " + std::string(std::to_string((fMallocMemoryOffset) * 8)) + " MB of RAM").c_str(), "SYSTEM-Z::Memory Test", 1);
                    uint64_t buffer_size = (fMallocMemoryOffset) * 1024 * 1024;
                    const uint64_t GB = 1024 * 1024 * 1024;

                    // Выделение памяти
                    uint64_t* buffer = nullptr;
                    ///stack_ptr = buffer;
                    try {
                        buffer = new uint64_t[buffer_size];
                    }
                    catch (const bad_alloc& e) {
                        ImGui::TextColored(ImVec4(1.0f, 0, 0.40f, 1.0f), "Memory allocation failed: %d", e.what());
                        MessageBoxA(hwnd, ("Memory allocation failed:\nError:" + std::string(e.what())).c_str(), "SYSTEM-Z::Memory Test", 1);
                        return EXIT_FAILURE;
                    }

                    // Тест записи
                    std::string stack_dump = "";
                    uint64_t* stack = 0;
                    //
                    dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "[MEMORY_TEST] STARTING stack_size:" << static_cast<float>((fMallocMemoryOffset * 8) / 1024) << " GB" << std::endl;
                    auto write_start = high_resolution_clock::now();
                    for (uint64_t i = 0; i < buffer_size; i++) {
                        buffer[i] = static_cast<uint64_t>(i % 256);
                       // SetWindowTextA(GetConsoleWindow(), ("[" + std::to_string(i) + " / " + std::to_string(buffer_size) + "]").c_str());
                    }
                    //dumpMemory << stack_dump << std::endl;
                    auto write_end = high_resolution_clock::now();

                    // Тест чтения и проверки
                    auto read_start = high_resolution_clock::now();
                    for (uint64_t i = 0; i < buffer_size; i++) {

                        if (buffer[i] != static_cast<uint64_t>(i % 256)) {
                            MessageBoxA(hwnd, ("Memory verification failed at position " + std::to_string(i)).c_str(), "SYSTEM-Z::Memory Test", 1);
                            cerr << "Memory verification failed at position " << i << endl;
                            delete[] buffer;
                            fCBenchMemory = false;
                            dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "Memory Bench Stop" << " stack_size:" << ((fMallocMemoryOffset) * 8) / 1024 << std::endl;
                            return EXIT_FAILURE;
                           // dumpMemory.close();

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
                    dumpMemory << Hour << ":" << Min << ":" << Sec << " INFO:" << "[MEMORY_TEST] Results\n"
                        << Hour << ":" << Min << ":" << Sec << " INFO:" << "WriteTest[" << static_cast<float>((fMallocMemoryOffset * 8) / 1024) << " GB] Time:" << write_time <<"ms | Speed:"<< write_speed <<" GB/s\n"
                        << Hour << ":" << Min << ":" << Sec << " INFO:" << "ReadTest[" << static_cast<float>((fMallocMemoryOffset * 8) / 1024) << "  GB] Time:" << read_time << "ms | Speed:" << read_speed <<" GB/s\n";
                    //
                    write_timeOut = write_time;
                    read_timeOut = read_time;
                    write_speedOut = write_speed;
                    read_speedOut = read_speed;
                    fCBenchMemory = false;
                    dumpMemory.close();
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
        ImDrawData* draw_data = ImGui::GetDrawData();
        const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
        if (!is_minimized)
        {
            wd->ClearValue.color.float32[0] = clear_color.x * clear_color.w;
            wd->ClearValue.color.float32[1] = clear_color.y * clear_color.w;
            wd->ClearValue.color.float32[2] = clear_color.z * clear_color.w;
            wd->ClearValue.color.float32[3] = clear_color.w;
            FrameRender(wd, draw_data);
            FramePresent(wd);
        }
    }

    // Cleanup
    err = vkDeviceWaitIdle(g_Device);
    vkDestroyImageView(init_info.Device, textureImageView, nullptr);
    vkDestroyImage(init_info.Device, textureImage, nullptr);
    vkFreeMemory(init_info.Device, textureImageMemory, nullptr);
    vkDestroyImageView(init_info.Device, textureImageView2, nullptr);
    vkDestroyImage(init_info.Device, textureImage2, nullptr);
    vkFreeMemory(init_info.Device, textureImageMemory2, nullptr);
    check_vk_result(err);
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    vkDestroySampler(g_Device, sampler, nullptr);
    CleanupVulkanWindow();
    CleanupVulkan();

    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

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
        if (g_Device != VK_NULL_HANDLE && wParam != SIZE_MINIMIZED)
        {
            // Resize swap chain
            int fb_width = (UINT)LOWORD(lParam);
            int fb_height = (UINT)HIWORD(lParam);
            if (fb_width > 0 && fb_height > 0 && (g_SwapChainRebuild || g_MainWindowData.Width != fb_width || g_MainWindowData.Height != fb_height))
            {
                ImGui_ImplVulkan_SetMinImageCount(g_MinImageCount);
                ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, &g_MainWindowData, g_QueueFamily, g_Allocator, fb_width, fb_height, g_MinImageCount);
                g_MainWindowData.FrameIndex = 0;
                g_SwapChainRebuild = false;
            }
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
