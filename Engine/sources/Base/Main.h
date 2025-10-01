#pragma once

#define RUN_PROJECT(proj) \
int main() { \
	auto game = new proj; \
	game->run(); \
	delete game; \
	return 0; \
}