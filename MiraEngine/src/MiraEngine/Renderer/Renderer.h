#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <SDL_render.h>
#include <SDL_video.h>

namespace Mira {

class MIRA_API Renderer {
public:
	Renderer(SDL_Window* _window);
	~Renderer();
	void clear(int r = 0u, int g = 0u, int b = 0u, int a = 0u);
	void renderBinded();
	SDL_Renderer* getRenderer() const;

private:
	SDL_Renderer* m_renderer;

};

} //namespace ends