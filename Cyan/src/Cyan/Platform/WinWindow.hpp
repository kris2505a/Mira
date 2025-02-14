#pragma once
#include "Cyan/GWindow.hpp"
#include "GLFW/glfw3.h"
#include "Cyan/Events/Event.hpp"

namespace Cyan {

	

	class winWindow : public GWindow {
		
		struct windowData {
			std::string title;
			unsigned int width, height;
			bool vSync;
			EventCallBackFn eventCallBack;

		};


	private:
		GLFWwindow* m_window;
		windowData m_data;


	private:
		virtual void init(const windowAttributes& attrib);
		virtual void shutDown();

	public:
		winWindow(const windowAttributes& attrib);
		virtual ~winWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		inline void setEventCallBack(const EventCallBackFn& callBack) override {
			m_data.eventCallBack = callBack;
		}
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	};
}
