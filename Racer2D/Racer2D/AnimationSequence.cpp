#include "pch.h"

#include "AnimationSequence.h"

namespace GameEngine
{

AnimationSequence::AnimationSequence(String^ animationName) :
		m_animationName(animationName)
{
	m_animations = ref new Vector<Animation ^>();
	m_freeze = false;
	m_currentFrame = 0;
	m_animationState = AnimationState::e_asNotRunning;
	m_animationMode = AnimationMode::e_amStopAtEnd;
}

AnimationSequence::~AnimationSequence()
{
	m_animations->Clear();
	m_animations = nullptr;
}

void AnimationSequence::Stop()
{
	m_animationState = AnimationState::e_asNotRunning;
}

void AnimationSequence::Update(float timeTotal, float timeDelta)
{
	bool fReset = false;

	if (!m_freeze)
	{
		// throw exception
	}
	
	if (m_currentFrame == m_maxFrame + 1)
	{
		if (m_animationMode == AnimationMode::e_amStopAtEnd)
		{
			m_animationState = AnimationState::e_asNotRunning;
			m_complete = true;
			return;
		}
		else if(m_animationMode == AnimationMode::e_amLoop)
		{
			m_animationState = AnimationState::e_asRunning;
			Reset();
		}
	}
	else if(m_animationState == AnimationState::e_asNotRunning)
	{
		return;
	}

	m_complete = false;

	for_each(begin(m_animations),
		end(m_animations),
		[&](Animation^ animation)
	{
		animation->Update(timeTotal, timeDelta);
	});
	
	m_currentFrame++;
}

void AnimationSequence::_AddAnimation(Animation^ animation)
{
	if (m_freeze)
	{
		// throw exception
	}

	m_animations->Append(animation);
	if (animation->StartFrame < m_minFrame)
	{
		m_minFrame = animation->StartFrame;
	}

	if (animation->EndFrame > m_maxFrame)
	{
		m_maxFrame = animation->EndFrame;
	}
}

void AnimationSequence::Reset()
{
	for_each(begin(m_animations),
		end(m_animations),
		[=](Animation^ animation)
	{
		animation->Reset();
	});

	m_currentFrame = 0;
}



}