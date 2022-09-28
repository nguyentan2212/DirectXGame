#pragma once
#include <chrono>

using namespace ::std::chrono;

class Timer
{
public:
    Timer(float fps);
    void Restart();
    bool Stop();
    bool Start();

    bool Tick(float& deltaTime);
    float GetMilisecondsElapsed(); // from start to now
    float GetMilisecondsDelta();   // from previous frame to current frame

private:
    bool isrunning = false;
    float current = 0;
    float mspf;
#ifdef _WIN32
    time_point<steady_clock> start;
    time_point<steady_clock> stop;
#else
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> stop;
#endif
};