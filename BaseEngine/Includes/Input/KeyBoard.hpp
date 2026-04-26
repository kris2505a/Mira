#pragma once
#include <array>

namespace Mira {

class Keyboard {
    friend class Window;
    friend class Input;

private:
    static void setKeyDown(size_t key) {
        keys[key] = true;
    }

    static void setKeyUp(size_t key) {
        keys[key] = false;
    }

private:
    inline static std::array<bool, 256> keys{};
};

}
