#pragma once
#include <string>
#include "mi_win_hpr.hpp"
#include "mi_core_api.hpp"

namespace mira::core {

MI_CORE_API auto toNarrow(std::wstring_view)    -> std::string;
MI_CORE_API auto toWide(std::string_view)       -> std::wstring;
MI_CORE_API auto getMessageFromHR(HRESULT hr)   -> std::string;

}
