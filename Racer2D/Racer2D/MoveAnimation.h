#pragma once

#include "Animation.h"
#include "GameObject.h"

using namespace Platform;

namespace GameEngine
{

ref class MoveAnimation : Animation
{
internal:
	MoveAnimation(String^ animationName,
							 GameObject^ object, 
							 float startX, 
							 float endX, 
							 float startY, 
							 float endY, 
							 int frameStart, 
							 int frameEnd);

	MoveAnimation(String^ animationName,
							GameObject^ object,
							float deltaX,
							float deltaY,
							int frameStart,
							int frameEnd);

public:
	virtual ~MoveAnimation();

	property float StartX
	{
		float get()
		{
			return m_startX;
		}
	}

	property float StartY
	{
		float get()
		{
			return m_startY;
		}
	}

	property float EndX
	{
		float get()
		{
			return m_endX;
		}
	}

	property float EndY
	{
		float get()
		{
			return m_endY;
		}
	}

	virtual void Update(int frame, int totalFrame, float timeTotal, float timeDelta) override;

private:
	float m_startX;
	float m_endX;

	float m_startY;
	float m_endY;

	float m_deltaX;
	float m_deltaY;

	GameObject^ m_gameObject;
};

}