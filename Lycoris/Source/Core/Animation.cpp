#include "Core/Animation.h"
#include "Extras/VisualEffect.h"

void Animation::Initialize(int maxFrame, VisualEffect* vfx) { if (maxFrame <= 0) { m_MaxFrames = 1; } m_MaxFrames = maxFrame; m_VFX = vfx; }

void Animation::SetLooped(bool val) { m_LoopAnimation = val; }

//Set Delay between each frame (in ms)
void Animation::SetFrameDelay(int val) { m_FrameDelay = val; }

void Animation::Play() { m_IsPlaying = true; }
void Animation::Stop() { m_IsPlaying = false; if (m_VFX != nullptr) { m_VFX->Callback(); } }
void Animation::ResetAnimation() { m_CurrentFrame = 0; }

void Animation::Update()
{
	if (m_IsPlaying)
	{
		m_CurrentFrame = static_cast<int>((SDL_GetTicks() / m_FrameDelay) % m_MaxFrames + 1);

		if (!m_LoopAnimation && m_CurrentFrame == (m_MaxFrames))
		{
			Stop();
		}
	}
}

bool Animation::IsLooped() const { return m_LoopAnimation; }
int Animation::GetCurrentFrame() const { return m_CurrentFrame; }