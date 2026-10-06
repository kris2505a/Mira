#pragma once
#include "mi_rhw_api.hpp"
#include <vulkan/vulkan.hpp>

MI_RHW

class MI_RHW_API Instance {
public:

private:
    vk::Instance m_instance;
    vk::DebugUtilsMessengerEXT m_debugMessenger;
};

MI_RHW_END