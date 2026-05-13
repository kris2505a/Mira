#pragma once
#include "Mira/Core/Core.h"

namespace Mira {


enum class EventCategory {
    WindowEvent         = BIT(1),
    KeyboardEvent       = BIT(2),
    MouseEvent          = BIT(3),
    InputEvent          = BIT(4),
    SystemEvent         = BIT(4)
};

class Event {
public:



};

}
