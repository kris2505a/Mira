#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
#include "Mira/Renderer/RHI/RHI.hpp"

#include <vector>

namespace Mira {

class VkRHI : public RHI {
public:
    VkRHI() = default;
    ~VkRHI() override = default;

    void initialize(WindowHandle& handle) override;
    void shutdown() override;

private:
    void createInstance();
    void setupDebugMessenger();
    void pickPhysicalDevice();

    std::vector <const char*> getRequiredExtensions();
    std::vector <const char*> getRequiredLayers();

    static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
        vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
        vk::DebugUtilsMessageTypeFlagsEXT type,
        const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

private:
    vk::raii::Context m_context;
    vk::raii::Instance m_instance = nullptr;
    vk::raii::DebugUtilsMessengerEXT m_debugMessenger = nullptr;
    vk::raii::PhysicalDevice m_physicalDevice = nullptr;



    WindowHandle& m_handle;
};

}
