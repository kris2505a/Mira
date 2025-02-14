#pragma once
#include "Core.hpp"
#include "Events/Event.hpp"
#include "GWindow.hpp"

namespace Cyan {

	class CYANAPI Game {
	private:
		std::unique_ptr <GWindow> m_window;
		bool m_isRunning;
	
	public:
		Game();
		virtual ~Game();
		void run();
	};

	Game* CreateGame();
}