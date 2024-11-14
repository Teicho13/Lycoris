#pragma once
#include <SDL.h>

struct DeltaTime
{
public:
	void Update()
	{
		//Calculate Delta time in seconds
		m_LastTime = m_Time;
		m_Time = SDL_GetPerformanceCounter();
		m_DeltaTime = (static_cast<float>(m_Time - m_LastTime) / static_cast<float>(SDL_GetPerformanceFrequency()));
	}

	void GetTime()
	{
		//Set Current Time
		m_Time = SDL_GetPerformanceCounter();
	}

	float GetSeconds() const { return m_DeltaTime; }
	float GetMilliseconds() const { return m_DeltaTime * 1000.f; }

private:
	Uint64 m_Time = 0;
	Uint64 m_LastTime = 0;

	float m_DeltaTime = 0;
};
