#pragma once

#include <collection.h>

#include "IUpdatable.h"
#include "Animation.h"

using namespace Platform;
using namespace Microsoft::WRL;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace GameEngine
{

ref class AnimationSequence : IUpdatable
{
internal:
	AnimationSequence(String^ animationName);

public:
	virtual ~AnimationSequence();

	virtual void Update(float timeTotal, float timeDelta);

	void AddAnimation(Animation^ animation)
	{
		// TODO: EndFrame > startFrame, else throw error

		_AddAnimation(animation);
	}

	void ResetAndStop()
	{
		Reset();
		Stop();
	}

	void Stop();

	void Reset();

	void Start()
	{
		m_animationState = AnimationState::e_asRunning;
	}

	void Freeze()
	{
		m_freeze = true;
	}

	property bool IsComplete
	{
		bool get()
		{
			return m_complete;
		}
	}

	property bool IsFrozen
	{
		bool get()
		{
			return m_freeze;
		}
	}

	property AnimationState State
	{
		AnimationState get()
		{
			return m_animationState;
		}
	}

	property AnimationMode Mode
	{
		AnimationMode get()
		{
			return m_animationMode;
		}

		void set(AnimationMode mode)
		{
			m_animationMode = mode;
		}
	}

	property String^ Name
	{
		String^ get()
		{
			return m_animationName;
		}
	}

private:

	void SetState(AnimationState state)
	{
		m_animationState = state;
	}

	void _AddAnimation(Animation^ animation);
	Vector<Animation^ >^ m_animations;

	AnimationState m_animationState;
	AnimationMode m_animationMode;

	int m_minFrame;
	int m_maxFrame;

	int m_currentFrame;

	bool m_freeze;
	bool m_complete;

	String^ m_animationName;
};

};