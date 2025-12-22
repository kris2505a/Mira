#pragma once
#include "Layer.h"
#include <d3d11.h>

namespace Mira {

class ImGuiLayer : public Layer {
public:
	ImGuiLayer(ID3D11Device* device, ID3D11DeviceContext* context, HWND handle);
	~ImGuiLayer();
	virtual void pulse(float deltaTime) override;
	virtual void render();
	virtual void signal(const Signal& s) override;

private:


};

}