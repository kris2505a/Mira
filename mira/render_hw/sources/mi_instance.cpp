#include "rhw/mi_instance.hpp"
#include <SDL3/SDL_vulkan.h>
#include <core/mi_log.hpp>

MI_RHW

void Instance::createInstance() {

    auto extensions = getWindowExtensions();

    vk::ApplicationInfo appInfo;
    appInfo.sType = vk::StructureType::eApplicationInfo;
    appInfo.pApplicationName = "Mira";
    appInfo.applicationVersion = vk::makeVersion(1, 0, 0);
    appInfo.pEngineName = "Mira";
    appInfo.engineVersion = vk::makeVersion(1, 0, 0);
    appInfo.apiVersion = vk::ApiVersion11;

    vk::InstanceCreateInfo createInfo;
    createInfo.sType = vk::StructureType::eInstanceCreateInfo;
    createInfo.pApplicationInfo = &appInfo;

    
}

core::Res<std::vector<const char*>, RError> Instance::getWindowExtensions() const {
    core::u32 extensionCount = 0;
    auto extensions = SDL_Vulkan_GetInstanceExtensions(&extensionCount);
    
    if (!extensions) {
        return core::Err<RError>({ ErrorType::FailedToRetrieveExtensions, "Failed to retrieve Extensions" });
    }

    std::vector<const char*> ext(extensions, extensions + extensionCount);

    auto required = vk::enumerateInstanceExtensionProperties();

    for (const char* i : ext) {
        auto found = std::ranges::any_of(required, [i](vk::ExtensionProperties& req){
            return std::strcmp(i, req.extensionName) == 0;
        });

        if (!found) {
            return core::Err<RError>({ ErrorType::ExtensionsNotSupported, std::string(i) });
        }
    }

    return ext;
}

MI_RHW_END