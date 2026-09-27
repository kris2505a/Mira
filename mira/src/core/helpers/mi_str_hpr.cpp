#include "mi_str_hpr.hpp"
#include <comdef.h>

namespace mira::core {

auto toNarrow(std::wstring_view str) -> std::string {
    if (str.empty()) {
        return {};
    }

    int size = WideCharToMultiByte(
        CP_UTF8,
        0,
        str.data(),
        static_cast<int>(str.size()),
        nullptr,
        0,
        nullptr,
        0
    );

    std::string result(size, '\0');
    WideCharToMultiByte(
        CP_UTF8,
        0,
        str.data(),
        static_cast<int>(str.size()),
        result.data(),
        size,
        nullptr,
        nullptr
    );
    return result;
}

auto toWide(std::string_view str) -> std::wstring {
    if (str.empty()) {
        return {};
    }

    int size = MultiByteToWideChar(
        CP_UTF8,
        0,
        str.data(),
        static_cast<int>(str.size()),
        nullptr,
        0
    );

    std::wstring result(size, L'\0');
    MultiByteToWideChar(
        CP_UTF8,
        0,
        str.data(),
        static_cast<int>(str.size()),
        result.data(),
        size
    );
    return result;
}

auto getMessageFromHR(HRESULT hr) -> std::string {
    _com_error err(hr);
    auto rawMsg = err.ErrorMessage();
    return toNarrow(std::wstring(rawMsg));
}

}
