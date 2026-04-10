#include <SDL3/SDL.h>
#include <iostream>

#include <RenderAPI.hpp>
#include <InputLayout.hpp>
#include <GraphicsFactory.hpp>

#include <SDL3/SDL_video.h>
#include <windows.h>

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
	api->setClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	//api->setWireFrameMode(true);

	bool running = true;

	SDL_Event e;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,   // bottom-left
		 0.5f, -0.5f, 0.0f,   // bottom-right
		 0.5f,  0.5f, 0.0f,   // top-right
		-0.5f,  0.5f, 0.0f    // top-left
	};

	auto vbo = graphicsFactory->createVertexBuffer(vertices, 4, 3 * sizeof(float));

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

	auto shader = graphicsFactory->createShader(L"Default", layout);


	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		api->preRenderSetup();
		api->clear();

		vbo->bind();
		ibo->bind();
		shader->bind();

		api->drawIndexed(6);

		api->swap();

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;


}