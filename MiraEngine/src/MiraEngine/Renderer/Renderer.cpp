#include <MiraPreCompHeader.h>
#include "Renderer.h"


namespace Mira {

Renderer::Renderer(SDL_Window* _window)
	: m_renderer(nullptr) {

	m_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

}

Renderer::~Renderer() {
	SDL_DestroyRenderer(m_renderer);
}

void Renderer::clear(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
}

void Renderer::renderBinded() {
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Renderer::getRenderer() const {
	return m_renderer;
}

}