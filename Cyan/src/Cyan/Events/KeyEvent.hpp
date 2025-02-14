#pragma once

#include "Event.hpp"

namespace Cyan {

	class CYANAPI KeyEvent : public Event {

	protected:
		int m_keyCode;
		KeyEvent(int keyCode) : m_keyCode(keyCode){}

	public:
		inline int getKeyCode() { return m_keyCode; }

		EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput)
	};


	class CYANAPI keyPressedEvent : public KeyEvent {
	
	private:
		int m_repeatCount;

	public:
		keyPressedEvent(int keyCode, int repeatedCount)
			: KeyEvent(keyCode), m_repeatCount(repeatedCount){ }
		inline int getRepeateCount() { return m_repeatCount; }

		virtual std::string toString() const  override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << "(" << m_repeatCount << ")";
			return ss.str();
		}
		EVENT_CLASS_TYPE(keyPressed)
	};

	class CYANAPI keyReleasedEvent : public KeyEvent {

	private:
		int m_repeatCount;

	public:
		keyReleasedEvent(int keyCode, int repeatedCount)
			: KeyEvent(keyCode), m_repeatCount(repeatedCount) {
		}
		inline int getRepeateCount() { return m_repeatCount; }

		virtual std::string toString() const  override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode << "(" << m_repeatCount << ")";
			return ss.str();
		}
		EVENT_CLASS_TYPE(keyRelesed)
	};


}