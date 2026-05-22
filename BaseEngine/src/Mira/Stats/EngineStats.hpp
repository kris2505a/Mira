#pragma once
#include "Mira/Core/Core.hpp"
#include "Mira/EngineComponents/Clock.hpp"

namespace Mira {

class MIRA_API EngineStats {
public:

	class MIRA_API DeltaTime {
		friend class Engine;
	public:
		static float inSeconds() {
			return static_cast<float>(deltaTime);
		}

		static float inMilliseconds() {
			return static_cast<float>(deltaTime) * 1000.0f;
		}

	private:
		static void updateDeltaTime() {
			float now = Clock::getTime();
			deltaTime = now - lastFrameTime;
			lastFrameTime = now;
		}
	
		static void initialize() {
			lastFrameTime = Clock::getTime();
		}

	private:
		inline static double deltaTime{ 0.0f };
		inline static double lastFrameTime{ 0.0f };
	};

	class MIRA_API WindowProperties {
		friend class Engine;

	public:
		static unsigned int getWidth() {
			return s_width;
		}

		static unsigned int getHeight() {
			return s_height;
		}

		static WindowHandle getHandle() {
			return s_handle;
		}

	private:
		static void setSize(unsigned int width, unsigned int height) {
			s_width = width;
			s_height = height;
		}

		static void setWindowHandle(WindowHandle handle) {
			s_handle = handle;
		}

		inline static unsigned int s_width{ 0 };
		inline static unsigned int s_height{ 0 };
		inline static WindowHandle s_handle{};

	};


};

}