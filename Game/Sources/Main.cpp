#include <SDL3/SDL.h>
#include <iostream>

#include <RenderAPI.hpp>
#include <InputLayout.hpp>
#include <GraphicsFactory.hpp>

#include <SDL3/SDL_video.h>
#include <windows.h>
#include <DirectXMath.h>

HWND GetHWND(SDL_Window* window)
{
	SDL_PropertiesID props = SDL_GetWindowProperties(window);

	return static_cast<HWND>(
		SDL_GetPointerProperty(
			props,
			SDL_PROP_WINDOW_WIN32_HWND_POINTER,
			nullptr
		)
	);
}

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Unable to init sdl!" << std::endl;
		return -1;
	}

	auto window = SDL_CreateWindow("Dx11-Window", 1280, 720, 0);

	if (!window) {
		std::cerr << "Unable to create window!" << std::endl;
		SDL_Quit();
		return -1;
	}

	auto graphicsFactory = mr::GraphicsFactory::create(mr::GraphicsAPI::DirectX11);

	auto api = graphicsFactory->createRenderAPI(GetHWND(window));
	//api->setWireFrameMode(true);

	bool running = true;

	SDL_Event e;

	float vertices[] = {
		// x      y      z       u     v
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   0.0f, 0.0f
	};

	auto vbo = graphicsFactory->createVertexBuffer(vertices, 4, 5 * sizeof(float));

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	auto ibo = graphicsFactory->createIndexBuffer(indices, 6);

	mr::InputLayout layout;
	layout.addLayout(
		{
			"POSITION",
			mr::LayoutDataType::Float,
			3,
			0
		}
	);

	layout.addLayout(
		{
			"TEXCOORD",
			mr::LayoutDataType::Float,
			2,
			0
		}
	);

	auto shader = graphicsFactory->createShader(L"Default", layout);

	DirectX::XMMATRIX model = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	);
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(45.0f),
		1280.0f / 720.0f,
		0.1f, 20.0f
	);
	
	auto mvp = DirectX::XMMatrixTranspose(model * view * proj);

	auto vcbo = graphicsFactory->createConstantBuffer(&mvp, sizeof(mvp), mr::ShaderType::VertexShader);
	
	struct alignas(16) TextureData {
		int texture = 1;
		float padding[3];
	};
	TextureData td;
	auto pcbo = graphicsFactory->createConstantBuffer(&td, sizeof(td), mr::ShaderType::PixelShader);

	auto texture = graphicsFactory->createTexture("texture/pizza.jpg");

	float angle = 0.0f;

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		if (angle > 360.0f) {
			angle = 0.0f;
		}

		angle += 1.0f;

		model = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angle));

		mvp = DirectX::XMMatrixTranspose(model * view * proj);

		vcbo->update(&mvp, sizeof(mvp));

		api->preRenderSetup();
		api->clear();

		vbo->bind();
		ibo->bind();
		shader->bind();
		vcbo->bind();
		pcbo->bind();
		texture->bind();

		api->drawIndexed(6);

		api->swap();

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;


}