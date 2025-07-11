#pragma once
#include "amd_ags.h"
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include "imgui_impl_vulkan.h"

#pragma comment(lib,"amd_ags_x64.lib")
uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter,
    VkMemoryPropertyFlags properties);
void createImage(VkDevice device, VkPhysicalDevice physicalDevice,
    uint32_t width, uint32_t height, VkFormat format,
    VkImageTiling tiling, VkImageUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkImage& image, VkDeviceMemory& imageMemory);

AGSGPUInfo gpuInfo;
int gpuIndex = 0;
AGSContext* context;
auto AGSInfo = std::make_unique<AGSDeviceInfo>();
uint64_t colorText(int64_t code) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)code);
    return 0;
}
uint64_t vkGetVRAMUsage(VkPhysicalDevice physicalDevice,int64_t *vkHeapAllMemSize,int64_t *vkHeapUsageMemSize) {
        VkPhysicalDeviceMemoryBudgetPropertiesEXT budgetProps = {};
        budgetProps.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;

        VkPhysicalDeviceMemoryProperties2 memProps2 = {};
        memProps2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
        memProps2.pNext = &budgetProps;

        vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &memProps2);

        for (uint32_t i = 0; i < memProps2.memoryProperties.memoryHeapCount; i++) {
           
            *vkHeapUsageMemSize = budgetProps.heapUsage[i] / (1024 * 1024);
            *vkHeapAllMemSize = budgetProps.heapBudget[i] / (1024 * 1024);
              
        }
        return 0;
}
void createBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size,
    VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
    VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    // Создание буфера
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create buffer!");
    }

    // Получение требований к памяти
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

    // Выделение памяти
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice,
        memRequirements.memoryTypeBits,
        properties);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate buffer memory!");
    }

    // Связывание буфера с памятью
    vkBindBufferMemory(device, buffer, bufferMemory, 0);
}
VkCommandPool VkGetCommandPool(VkDevice device, uint32_t queue) {
    VkCommandPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pool_info.queueFamilyIndex = queue;

    VkCommandPool command_pool = VK_NULL_HANDLE;
    VkResult result = vkCreateCommandPool(device, &pool_info, nullptr, &command_pool);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Failed to create command pool: %d\n", result);
        return VK_NULL_HANDLE;
    }
    return command_pool;
}
uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter,
    VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
}
void createImage(VkDevice device, VkPhysicalDevice physicalDevice,
    uint32_t width, uint32_t height, VkFormat format,
    VkImageTiling tiling, VkImageUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkImage& image, VkDeviceMemory& imageMemory) {
    // Создание изображения
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = usage;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.flags = 0; // Optional

    if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image!");
    }

    // Выделение памяти для изображения
    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, image, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice,
        memRequirements.memoryTypeBits,
        properties);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate image memory!");
    }

    // Связывание изображения с памятью
    vkBindImageMemory(device, image, imageMemory, 0);
}
VkImageView createImageView(VkDevice device, VkImage image, VkFormat format,
    VkImageAspectFlags aspectFlags) {
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;
    if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create texture image view!");
    }

    return imageView;
}
std::string ConsolePutColored(std::string data, int64_t code) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)code);
    std::cout << data << std::endl;
    SetConsoleTextAttribute(hStdOut, (WORD)15);
    return "";
}

class CVkImage {
public:
    int64_t LoadImageToMemory(const char* filename, VkImage* out_texture, VkImageView* out_texture_view,
        int* out_width, int* out_height, VkDeviceMemory* out_texture_memory,
        VkFormat* out_format = nullptr);
    void Init(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool);
    void Cleanup();

private:
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    VkDevice m_device = VK_NULL_HANDLE;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkQueue m_queue = VK_NULL_HANDLE;
    VkCommandPool m_commandPool = VK_NULL_HANDLE;
};

// Инициализация (должна быть вызвана после создания Vulkan устройства)
void CVkImage::Init(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkCommandPool commandPool) {
    m_device = device;
    m_physicalDevice = physicalDevice;
    m_queue = queue;
    m_commandPool = commandPool;
}

int64_t CVkImage::LoadImageToMemory(const char* filename, VkImage* out_texture, VkImageView* out_texture_view,
    int* out_width, int* out_height, VkDeviceMemory* out_texture_memory,
    VkFormat* out_format) {
    // Загрузка изображения с помощью stb_image
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(filename, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    if (!pixels) {
        fprintf(stderr, "Failed to load texture: %s\nReason: %s\n",
            filename, stbi_failure_reason());
        return false;
    }
    printf("Loaded image: %dx%d, channels: %d\n", texWidth, texHeight, texChannels);

    VkDeviceSize imageSize = texWidth * texHeight * 4;
    *out_width = texWidth;
    *out_height = texHeight;
    VkFormat format = VK_FORMAT_R8G8B8A8_SRGB;
    if (out_format) *out_format = format;

    // Создание временного буфера
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(m_device, m_physicalDevice, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingBuffer, stagingBufferMemory);

    // Копирование данных пикселей в буфер
    void* data;
    vkMapMemory(m_device, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(m_device, stagingBufferMemory);

    stbi_image_free(pixels);

    // Создание изображения Vulkan
    createImage(m_device, m_physicalDevice, texWidth, texHeight, format,
        VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, *out_texture, *out_texture_memory);

    // Переход изображения в правильный layout и копирование данных
    transitionImageLayout(*out_texture, format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(stagingBuffer, *out_texture, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    transitionImageLayout(*out_texture, format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    // Очистка временного буфера
    vkDestroyBuffer(m_device, stagingBuffer, nullptr);
    vkFreeMemory(m_device, stagingBufferMemory, nullptr);

    // Создание image view
    *out_texture_view = createImageView(m_device, *out_texture, format, VK_IMAGE_ASPECT_COLOR_BIT);

    return true;
}

void CVkImage::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else {
        throw std::invalid_argument("Unsupported layout transition!");
    }

    vkCmdPipelineBarrier(
        commandBuffer,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
    );

    endSingleTimeCommands(commandBuffer);
}

void CVkImage::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = { 0, 0, 0 };
    region.imageExtent = { width, height, 1 };

    vkCmdCopyBufferToImage(
        commandBuffer,
        buffer,
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region
    );

    endSingleTimeCommands(commandBuffer);
}

VkCommandBuffer CVkImage::beginSingleTimeCommands() {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = m_commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(m_device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void CVkImage::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(m_queue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(m_queue);

    vkFreeCommandBuffers(m_device, m_commandPool, 1, &commandBuffer);
}
auto CVk = std::make_unique< CVkImage>();
class AMD_GPU {
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
   int64_t  vkMemUsage = 0;
   int64_t  vkMemHeapSize = 0;
   std::string AGSInfoText; bool GPUNotAMD;
   std::string GPUInitMsg;
   int64_t SYSTEM_Z(std::string* outText);
   uint64_t wx = 600; uint64_t wy = 800;
   bool agsCheck();
   void agsShutdown();
   bool fAGSState = false;
  
};
int64_t AMD_GPU::SYSTEM_Z(std::string *outText) {
    static int64_t blink = 0;
    static int64_t inDelay = 0;
    static bool bRevertText = 0;
    std::string fAText[] = {"SYSTEM-Z 1.2" };
    inDelay++;
    if (inDelay > 10) {
        inDelay = 0;
        blink++;
    }
    if (blink > 1) { blink = 0; }
    *outText = (fAText[0] + (blink ? "|" : " ")).c_str();
}
bool AMD_GPU::agsCheck() {
    AGSReturnCode code = agsInitialize(AGS_CURRENT_VERSION, nullptr, &context, &gpuInfo);
    if ((code) == AGS_FAILURE) {
        colorText(47);
        AMD_GPU::GPUInitMsg = "AGS::Init() -> Fatal Error!!";
        MessageBoxA(AMD_GPU::hwnd,"AGS::Init() -> Fatal Error!!","SYSTEM-Z::AMD_GPU",1);
    }
    if ((code) == AGS_SUCCESS) {
        AMD_GPU::fAGSState = true;
        colorText(37);
        AMD_GPU::GPUInitMsg = "Your GPU is AMD!!AGS::Init()->OK";
        colorText(15);
        *AGSInfo = gpuInfo.devices[gpuIndex];
        AMD_GPU::GPUlocalMemory = AGSInfo->localMemoryInBytes;
        AMD_GPU::GPUSharedMemory = AGSInfo->sharedMemoryInBytes;
        AMD_GPU::GPUCoreClock = AGSInfo->coreClock;
        AMD_GPU::GPUMemoryClock = AGSInfo->memoryClock;
        AMD_GPU::GPUNumberCUs = AGSInfo->numCUs;
        AMD_GPU::GPUNumberROPs = AGSInfo->numROPs;
        AMD_GPU::GPUNumberWGPs = AGSInfo->numWGPs;
        AMD_GPU::GPUMemoryBandwidth = AGSInfo->memoryBandwidth / 1024.0f;
        AMD_GPU::GPUTeraFlops = AGSInfo->teraFlops;
       // AMD_GPU_FAKE::AGSInfoText = "AGS_SDK:OK";
        GPUNotAMD = true;
        return 0;
    }
}
void AMD_GPU::agsShutdown() {
    AGSReturnCode code = agsDeInitialize(*&context);
   // AMD_GPU::GPUInitMsg = (code == AGS_SUCCESS) ? "AGS::ShutDown() - OK" : "AGS::ShutDown() - Fatal Error" ;
   fAGSState = (code == AGS_SUCCESS) ? true : false;
}
uint64_t a = 0;
auto AGPU = std::make_unique<AMD_GPU>();


