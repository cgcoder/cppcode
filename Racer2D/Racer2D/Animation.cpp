#include "pch.h"

#include "Animation.h"

namespace GameEngine
{

Animation::Animation(String^ animationName, int startFrame, int endFrame) :
	m_animationName(animationName)
{
	m_startFrame = startFrame;
	m_endFrame = endFrame;
}

Animation::~Animation()
{
}

void Animation::Update(int frame, int totalFrame, float timeTotal, float timeDelta)
{
}

};