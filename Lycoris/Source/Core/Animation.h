#pragma once
#include <SDL_timer.h>

class VisualEffect;
struct Animation
{
	void Initialize(int maxFrame, VisualEffect* vfx = nullptr);

	void SetLooped(bool val);

	//Set Delay between each frame (in ms)
	void SetFrameSpeed(float val);

	void Play();
	void Stop();
	void ResetAnimation();

	void Update(const float dt);

	bool IsLooped() const;
	int GetCurrentFrame() const;

private:
	bool m_IsPlaying = false;
	bool m_LoopAnimation = true;
	
	float m_FrameSpeed = 1.f;

	int m_CurrentFrame = 0;
	int m_MaxFrames = 0;

	VisualEffect* m_VFX = nullptr;

	float m_time = 0.0f;
};
