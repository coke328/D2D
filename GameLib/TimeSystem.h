#pragma once
#include "pch.h"

class d2dWinApp;

class TimeSystem
{
	friend class d2dWinApp;
	friend class Timer;

	LARGE_INTEGER frequency;
	LARGE_INTEGER lastCount;
	LARGE_INTEGER currCount;
	float deltaTime;
	float fixedUpdateInterval;
	float fixedDeltaTime;

	TimeSystem() = default;

	void InitTime();
	void UpdateTime();
	void FixedUpdate(float dt);

public:
	static TimeSystem& GetInstance();

	float GetDeltaTime();
	float GetFixedUpdateInterval();
	float GetFixedDeltaTime();
	void SetFixedUpdateInterval(float fps);
};

class Timer {
public:
	Timer();
	bool TimePassed(float time);
	void Reset();
	bool TimePassed();
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER lastCount;
	LARGE_INTEGER currCount;
};