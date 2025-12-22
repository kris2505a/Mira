#include <PreCompHeader.h>
#include "ImGuiLayer.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

namespace Mira {

ImGuiLayer::ImGuiLayer(ID3D11Device* device, ID3D11DeviceContext* context, HWND handle) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(handle);
	ImGui_ImplDX11_Init(device, context);
}

void ImGuiLayer::render() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
		
	ImGui::Begin("Test Window");

	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::signal(const Signal& s) {

}

void ImGuiLayer::pulse(float deltaTime) {

}

ImGuiLayer::~ImGuiLayer() {
	ImGui::DestroyContext();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

}