#pragma once
#include <SDL_timer.h>

class VisualEffect;
struct Animation
{
	void Initialize(int maxFrame, VisualEffect* vfx = nullptr);

	void SetLooped(bool val);

	//Set Delay between each frame (in ms)
	void SetFrameDelay(int val);

	void Play();
	void Stop();
	void ResetAnimation();

	void Update();

	bool IsLooped() const;
	int GetCurrentFrame() const;

private:
	bool m_IsPlaying = false;
	bool m_LoopAnimation = true;

	//Delay in ms
	int m_FrameDelay = 1000;

	int m_CurrentFrame = 0;
	int m_MaxFrames = 0;

	VisualEffect* m_VFX = nullptr;
};
