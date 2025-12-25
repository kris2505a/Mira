#include <PreCompHeader.hpp>
#include "ImGuiLayer.hpp"
#include <imgui.h>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>

namespace Mira {

ImGuiLayer::ImGuiLayer(ID3D11Device* device, ID3D11DeviceContext* context, HWND handle) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(handle);
	ImGui_ImplDX11_Init(device, context);
}

void ImGuiLayer::render() {



	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

	renderUiElements();


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

}

void ImGuiLayer::signal(const Signal& s) {

}

void ImGuiLayer::pulse(float deltaTime) {

}

void ImGuiLayer::renderUiElements() {
	ImGui::Begin("Console");


	ImGui::End();
}

ImGuiLayer::~ImGuiLayer() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

}