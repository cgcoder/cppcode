#pragma once

#include "IUpdatable.h"
#include "AnimationConstants.h"

namespace GameEngine
{

ref class AnimationStoryBoard;

ref class Animation : IUpdatable
{
internal:
	Animation(String^ animationName, int StartFrame, int EndFrame);

	void ResetTicks()
	{
		m_totalFrame = 0;
		m_frame = 0;
	}

public:
	virtual ~Animation();

	virtual void Update(float timeTotal, float timeDelta)
	{
		if (m_totalFrame >= m_startFrame && m_totalFrame <= m_endFrame)
		{
			m_frame++;
			Update(m_frame, m_totalFrame, timeTotal, timeDelta);
		}
		else
		{
			int i = 0;
			i++;
		}
		m_totalFrame++;
	}

	virtual void Update(int frame, int totalFrame, float timeTotal, float timeDelta);

	virtual void Reset()
	{
		m_totalFrame = 0;
		m_frame = 0;
	}

	property AnimationStoryBoard^ StoryBoard
	{
		AnimationStoryBoard^ get()
		{
			return m_storyBoard;
		}
	}

	property String^ Name
	{
		String^ get()
		{
			return m_animationName;
		}
	}

	property int StartFrame
	{
		int get()
		{
			return m_startFrame;
		}
	}

	property int EndFrame
	{
		int get()
		{
			return m_endFrame;
		}
	}

private protected:
	AnimationStoryBoard^ m_storyBoard;
	String^ m_animationName;

	int m_frame;
	int m_totalFrame;

	int m_startFrame;
	int m_endFrame;
};

};