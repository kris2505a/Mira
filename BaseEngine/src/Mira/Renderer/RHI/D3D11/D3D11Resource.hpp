#pragma once
#include <d3d11.h>
#include "Mira/Logger/Logger.hpp"
#include <stdexcept>

namespace Mira {

class D3D11Resource {
public:
	static void setResource(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) {
		s_device = pDevice;
		s_context = pContext;
	}

	static ID3D11Device* getDevice() {
	    if (!s_device) {
	        Logger::log(LogType::Error, "Device not initialized!");
	        throw std::runtime_error("RHI not initialized yet!");
	    }
		return s_device;
	}

	static ID3D11DeviceContext* getContext() {
	    if (!s_context) {
	        Logger::log(LogType::Error, "Context not initialized!");
	        throw std::runtime_error("RHI not initialized yet!");
	    }
	    return s_context;
	}


private:
	inline static ID3D11Device* s_device = nullptr;
	inline static ID3D11DeviceContext* s_context = nullptr;
};
}