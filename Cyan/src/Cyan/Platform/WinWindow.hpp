#pragma once
#include "Cyan/GWindow.hpp"
#include "Cyan/Events/Event.hpp"
#include "Cyan/Events/AppEvent.hpp"
#include "Cyan/Events/KeyEvent.hpp"
#include "Cyan/Events/MouseEvent.hpp"

struct GLFWwindow;
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
