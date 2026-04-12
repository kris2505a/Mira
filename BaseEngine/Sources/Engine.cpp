#include <Core/Engine.hpp>
#include <Logging/Log.hpp>


namespace Mira {

Engine::Engine() = default;
Engine::~Engine() = default;

void Engine::run() {
	init();
	mainLoop();
	cleanup();
}

void Engine::init() {
	Logger::Log(LogType::Info, "Engine Init");
}

void Engine::cleanup() {
	Logger::Log(LogType::Info, "Engine Cleanup");
}

void Engine::mainLoop() {
	while (true) {
		Logger::Log(LogType::Info, "MainLoop: {}", m_test++);
	}
}

void Engine::update() {

}

void Engine::render() {

}

}