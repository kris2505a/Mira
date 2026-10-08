#pragma once
#include "mi_rhw_api.hpp"
#include <vulkan/vulkan.hpp>
#include <SDL3/SDL_video.h>

#include "mi_rhw_errors.hpp"
#include <core/mi_types.hpp>


MI_RHW

class MI_RHW_API Instance {
public:

private:
    void createInstance();
    core::Res<std::vector<const char*>, RError> getWindowExtensions() const;

private:
    vk::Instance m_instance;
    vk::DebugUtilsMessengerEXT m_debugMessenger;
    SDL_Window* p_window; // TODO: implement something lik a NotNull class that can assert this to be not null 
};

MI_RHW_END
