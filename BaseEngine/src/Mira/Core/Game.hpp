#pragma once
#include "Core.hpp"

namespace Mira 
{

class MIRA_API Game {
public:
	virtual auto update() -> void = 0;
	Game() = default;
	virtual ~Game() = default;

	template <typename T> 
	static Scope<T> createGame() {
		if constexpr (!std::is_base_of_v<Game, T>) {
			static_assert(false, "T is not a derived class of Game");
		}
		return createScope<T>();
	}
};

}