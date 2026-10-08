#pragma once
#include "mi_rhw_api.hpp"
#include <string>

MI_RHW

enum class ErrorType {
    FailedToRetrieveExtensions,
    ExtensionsNotSupported,
    LayersNotSupported
};

class RError {
    friend std::ostream& operator<<(std::ostream& ostr, const Error& err) {
        ostr << err.m_message;
        return ostr;
    }

public:
    RError(ErrorType error, std::string_view message) 
        : m_errorType(error), m_message(message) {}
    
private:
    ErrorType m_errorType;
    std::string m_message;
};

MI_RHW_END