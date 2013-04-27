#include "pch.h"

#include "MoveAnimation.h"

namespace GameEngine
{

MoveAnimation::MoveAnimation(String^ animationName,
							 GameObject^ object, 
							 float startX, 
							 float endX, 
							 float startY, 
							 float endY, 
							 int frameStart, 
							 int frameEnd) :
		Animation(animationName, frameStart, frameEnd),
		m_gameObject(object),
		m_startX(startX),
		m_endX(endX),
		m_startY(startY),
		m_endY(endY)
{
	m_deltaX = (m_endX - m_startX) / (m_endFrame - m_startFrame);
	m_deltaY = (m_endY - m_startY) / (m_endFrame - m_startFrame);
}

MoveAnimation::MoveAnimation(String^ animationName,
							GameObject^ object,
							float deltaX,
							float deltaY,
							int frameStart,
							int frameEnd) : 
	Animation(animationName, frameStart, frameEnd),
	m_gameObject(object)
{
	m_startX = object->Position.x;
	m_startX = object->Position.y;

	m_endX = m_startX + deltaX;
	m_endY = m_startY + deltaY;

	m_deltaX = deltaX / (m_endFrame - m_startFrame);
	m_deltaY = deltaY / (m_endFrame - m_startFrame);
}

MoveAnimation::~MoveAnimation()
{
	m_gameObject = nullptr;
}

void MoveAnimation::Update(int frame, int totalFrame, float timeTotal, float timeDelta)
{
	m_gameObject->Position = Point2F(m_gameObject->Position.x + m_deltaX, m_gameObject->Position.y + m_deltaY);
}

};