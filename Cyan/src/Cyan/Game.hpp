#pragma once
#include "Core.hpp"

namespace Cyan {

	class CYANAPI Game {
	public:

		Game();
		virtual ~Game();
		void run();
	};

	Game* CreateGame();
}