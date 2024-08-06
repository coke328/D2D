#include "pch.h"
#include "TimeSystem.h"

TimeSystem& TimeSystem::GetInstance()
{
	static TimeSystem timeSystem;
	return timeSystem;
}

void TimeSystem::InitTime()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastCount);

	SetFixedUpdateInterval(60);
}

void TimeSystem::UpdateTime()
{
	QueryPerformanceCounter(&currCount);
	deltaTime = static_cast<float>(currCount.QuadPart - lastCount.QuadPart) / static_cast<float>(frequency.QuadPart);

	lastCount = currCount;
}

void TimeSystem::FixedUpdate(float dt)
{
	fixedDeltaTime = dt;
}

float TimeSystem::GetDeltaTime()
{
	return deltaTime;
}

float TimeSystem::GetFixedUpdateInterval()
{
	return fixedUpdateInterval;
}

float TimeSystem::GetFixedDeltaTime()
{
	return fixedDeltaTime;
}

void TimeSystem::SetFixedUpdateInterval(float fps)
{
	fixedUpdateInterval = 1.0f / fps;
}

Timer::Timer()
{
	QueryPerformanceCounter(&lastCount);
	frequency = TimeSystem::GetInstance().frequency;
}

bool Timer::TimePassed(float time)
{
	return time < TimePassed();
}

void Timer::Reset()
{
	QueryPerformanceCounter(&lastCount);
}

bool Timer::TimePassed()
{
	QueryPerformanceCounter(&currCount);
	return static_cast<float>(currCount.QuadPart - lastCount.QuadPart) / 
		static_cast<float>(frequency.QuadPart);
}
