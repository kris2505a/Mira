#pragma once
#include "PreCompHeaders.hpp"
#include "Cyan/core.hpp"
#include "Events/Event.hpp"


namespace Cyan {

	struct windowAttributes {
		std::string windowTitle;
		unsigned int windowWidth;
		unsigned int windowHeight;

		windowAttributes(const std::string& title = "Cyan Vilayaatu Iyanthiram", unsigned int width = 1600, unsigned int height = 900)
			: windowTitle(title), windowWidth(width), windowHeight(height){ }
	};

	class CYANAPI GWindow {
	
	public:
		using EventCallBackFn = std::function<void(Event&)>;
		//using is the same shit which was called with the name 'typedef' before
		virtual ~GWindow();
		virtual void onUpdate();

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallBack(const EventCallBackFn& callBack) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static GWindow* createWindow(const windowAttributes& attributes = windowAttributes());
	};

}
