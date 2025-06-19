#include <Engine.h>

class API SandBox : public GameApp {
private:
	bool m_isRunning = true;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

public:
	SandBox() {
		SDL_Init(SDL_INIT_VIDEO);
		m_window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	}

	~SandBox() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	virtual void run() override {
		SDL_Event event;
		while (m_isRunning) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					m_isRunning = false;
			}
			SDL_SetRenderDrawColor(m_renderer, 0u, 0u, 0u, 255u);
			SDL_RenderClear(m_renderer);
			SDL_RenderPresent(m_renderer);
		}
	}
};

GameApp* createGameApp() {
	return new SandBox();
}