#pragma once

#define RUN_PROJECT(proj) \
int main(int argc, char** argv) { \
	auto game = new proj; \
	game->run(); \
	delete game; \
	return 0; \
}