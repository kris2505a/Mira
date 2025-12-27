#pragma once
#include "Layer.hpp"
#include <d3d11.h>

namespace Mira {

class ImGuiLayer : public Layer {
public:
	ImGuiLayer(ID3D11Device* device, ID3D11DeviceContext* context, HWND handle);
	~ImGuiLayer();
	void pulse(float deltaTime) override;
	void render();
	void signal(const Signal& s) override;
	
	static void begin();
	static void end();

private:
	void renderUiElements();

};

}