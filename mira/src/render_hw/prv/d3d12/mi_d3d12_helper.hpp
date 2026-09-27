#pragma once
#include <helpers/mi_str_hpr.hpp>
#include <helpers/mi_win_hpr.hpp>
#include <log/mi_log.hpp>

namespace mira::rhw {

inline void throwOnFailure(HRESULT hr, std::string_view msg) {
    if (FAILED(hr)) {
        core::Log::error("{}: {}", msg, core::getMessageFromHR(hr));
        throw std::runtime_error("d3d12 failure");
    }
}

}