#include "Core/Animation.h"

#include <iostream>

#include "Extras/VisualEffect.h"

void Animation::Initialize(int maxFrame, VisualEffect* vfx) { if (maxFrame <= 0) { m_MaxFrames = 1; } m_MaxFrames = maxFrame; m_VFX = vfx; }

void Animation::SetLooped(bool val) { m_LoopAnimation = val; }

//Set how fast we count up towards the next frame (FrameSpeed * DT)
void Animation::SetFrameSpeed(float val) { m_FrameSpeed = val; }

void Animation::Play() { m_IsPlaying = true; }
void Animation::Stop() { m_IsPlaying = false; if (m_VFX != nullptr) { m_VFX->Callback(); } }
void Animation::ResetAnimation() { m_CurrentFrame = 0; }

void Animation::Update(const float dt)
{
	if(m_IsPlaying)
	{
		m_time += m_FrameSpeed * dt;
		if(m_time >= 1)
		{
			m_CurrentFrame++;
			m_time = 0.f;

			if(m_CurrentFrame > m_MaxFrames)
			{
				if(m_LoopAnimation)
				{
					m_CurrentFrame = 0;
				}
				else
				{
					Stop();
				}
			}
		}
	}
	
}

bool Animation::IsLooped() const { return m_LoopAnimation; }
int Animation::GetCurrentFrame() const { return m_CurrentFrame; }