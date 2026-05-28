#include "MiraPch.hpp"
#include "VkRHI.hpp"
#include "Mira/Core/Assert.hpp"

#include <GLFW/glfw3.h>



namespace Mira {

void VkRHI::initialize(WindowHandle& handle) {
    m_handle = handle;
}

std::vector <const char*> VkRHI::getRequiredExtensions() {
    uint32_t count = 0;
    auto extensions = glfwGetRequiredInstanceExtensions(&count);

    std::vector glfwExtensions(extensions, extensions + count);

    #if defined (MIRA_DEBUG)
    glfwExtensions.push_back(vk::EXTDebugUtilsExtensionName);
    #endif


    auto extensionProperties = m_context.enumerateInstanceExtensionProperties();

    for (const char* ext : glfwExtensions) {

        auto result = std::ranges::none_of(
            extensionProperties,
            [ext](const auto& extension) {
                return strcmp(extension.extensionName, ext) == 0;
            }
        );

        MIRA_ASSERT(!result, "Required GLFW extensions not supported: " + std::string(ext));
    }

    return glfwExtensions;
}

std::vector<const char*> VkRHI::getRequiredLayers() {
    std::vector<const char*> layers;

    #if defined (MIRA_DEBUG)
    layers.push_back("VK_LAYER_KHRONOS_validation");
    #endif  

    auto layerProperties = m_context.enumerateInstanceLayerProperties();

    for (const char* layer : layers) {
        bool result = std::ranges::any_of(layerProperties.begin(), layerProperties.end(), [layer](const auto& reqLayer) {
            return strcmp(layer, reqLayer.layerName) == 0;
        });

        MIRA_ASSERT(result, "Required layer not supported: " + std::string(layer));

    }
    return layers;
}

void VkRHI::createInstance() {

    auto glfwExtensions = getRequiredExtensions();
    auto layers = getRequiredLayers();

    constexpr vk::ApplicationInfo appInfo {
        .pApplicationName = "Sandbox",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "Mira",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = vk::ApiVersion13
    };

    vk::InstanceCreateInfo createInfo {
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size()),
        .ppEnabledExtensionNames = glfwExtensions.data(),
        .enabledLayerCount = static_cast<uint32_t>(layers.size()),
        .ppEnabledLayerNames = layers.data()
    };

    m_instance = vk::raii::Instance(m_context, createInfo);

}

void VkRHI::setupDebugMessenger() {
#ifndef MIRA_DEBUG
    return;
#endif

    vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
    );

    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags (
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
    );

    vk::DebugUtilsMessengerCreateInfoEXT createInfo {
        .messageSeverity = severityFlags,
        .messageType = messageTypeFlags,
        .pfnUserCallback = &VkRHI::debugCallback
    };

    m_debugMessenger = m_instance.createDebugUtilsMessengerEXT(createInfo);
    
}

 VKAPI_ATTR vk::Bool32 VKAPI_CALL VkRHI::debugCallback(
        vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
        vk::DebugUtilsMessageTypeFlagsEXT type,
        const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
) {

    Logger::log(LogType::Debug, "Validation layer: Type-> {} => Msg-> {}", vk::to_string(type), pCallbackData->pMessage);
    return vk::False;
}

void VkRHI::pickPhysicalDevice() {
    auto devices = m_instance.enumeratePhysicalDevices();
    MIRA_ASSERT(!devices.empty(), "Failed to find gpu with vulkan support");
    
    std::multimap<int, vk::raii::PhysicalDevice> candidates;
    for (auto& pd : devices) {
        auto deviceProp = pd.getProperties();
        auto deviceFeat = pd.getFeatures();

        uint32_t score = 0;

        if (deviceProp.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
            score += 1000;
        }

        score += deviceProp.limits.maxImageDimension2D;

        if (!deviceFeat.geometryShader) {
            continue;
        }

        candidates.insert(std::make_pair(score, pd));
    }

    if (!candidates.empty() && candidates.rbegin()->first > 0) {
        m_physicalDevice = candidates.rbegin()->second;
    }
    else {
        Logger::log(LogType::Error, "Failed to pick physical device");
        std::abort();
    }
}


} //namespace Mira
