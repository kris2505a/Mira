#include "MiraPch.hpp"
#include "RHI.hpp"
#include "D3D11/D3D11RHI.hpp"
#include "Mira/Logger/Logger.hpp"

namespace Mira {

API RHI::s_api = API::None;

Scope<RHI> RHI::createRHI(API api) {

    s_api = api;

    switch (s_api) {
    case API::D3D11:
        return createScope<D3D11RHI>();

    default:
    {
        Logger::log(LogType::Error, "Invalid Graphics API!");
        throw std::runtime_error("Invalid Graphics API!");
    }

    }
}

API RHI::getCurrentAPI() {
    return s_api;
}

}