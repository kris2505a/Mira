#pragma once
#include "core.hpp"

namespace Cyan {

	class CYANAPI Game {
	public:

		Game();
		virtual ~Game();
		void run();
	};

	Game* CreateGame();
}