#include <PreCompHeader.hpp>
#include "Timer.hpp"

namespace Mira {

Timer::Timer() {
    m_currentTime = std::chrono::high_resolution_clock::now();
    m_previousTime = std::chrono::high_resolution_clock::now();
}

float Timer::elapsed() {
    m_currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration <float> elapsedTime = m_currentTime - m_previousTime;
    m_previousTime = m_currentTime;
    return elapsedTime.count();
}

}