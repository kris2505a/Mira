#include "MiraPch.h"
#include "RHI.h"
#include "D3D11/D3D11RHI.h"
#include "Mira/Logger/Logger.h"

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