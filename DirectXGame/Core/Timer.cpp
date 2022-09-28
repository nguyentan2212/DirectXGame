#include "Timer.h"

Timer::Timer(float fps)
{
	start = high_resolution_clock::now();
	stop = high_resolution_clock::now();
	this->mspf = 1 / fps * 1000;
}

void Timer::Restart()
{
	start = high_resolution_clock::now();
	stop = high_resolution_clock::now();
}

float Timer::GetMilisecondsElapsed()
{
	if (isrunning)
	{
		auto elapsed = duration<float, std::milli>(high_resolution_clock::now() - start);
		return elapsed.count();
	}
	else
	{
		auto elapsed = duration<float, std::milli>(stop - start);
		return elapsed.count();
	}
}

float Timer::GetMilisecondsDelta()
{
	float delta = 0;
	Tick(delta);
	return delta;
}

bool Timer::Stop()
{
	if (!isrunning)
		return false;
	else
	{
		stop = high_resolution_clock::now();
		isrunning = false;
		return true;
	}
}

bool Timer::Start()
{
	if (isrunning)
	{
		return false;
	}
	else
	{
		start = high_resolution_clock::now();
		isrunning = true;
		return true;
	}
}

bool Timer::Tick(float& deltaTime)
{
	float elapsed = GetMilisecondsElapsed();
	float delta = elapsed - current;
	if (delta > mspf)
	{
		current = elapsed;
		deltaTime = delta;
		return true;
	}
	return false;
}
