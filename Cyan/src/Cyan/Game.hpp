#pragma once
#include "Core.hpp"
#include "Events/Event.hpp"
#include "GWindow.hpp"
#include "Events/AppEvent.hpp"


namespace Cyan {

	class CYANAPI Game {
	private:
		std::unique_ptr <GWindow> m_window;
		bool m_isRunning;
	
	public:
		Game();
		virtual ~Game();
		void run();
		void onEvent(Event& event);
		bool onClose(windowCloseEvent& event);
	};

	Game* CreateGame();
}