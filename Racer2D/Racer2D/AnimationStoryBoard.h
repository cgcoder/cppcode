#pragma once

#include <collection.h>

#include "IUpdatable.h"
#include "AnimationConstants.h"

using namespace Platform;
using namespace Microsoft::WRL;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace GameEngine
{

ref class AnimationSequence;

delegate void AnimationEventDelegate(AnimationSequence ^, GameEngine::AnimationEvent);

ref class AnimationStoryBoard : IUpdatable
{
internal:
	AnimationStoryBoard();

public:
	virtual ~AnimationStoryBoard();

	void AddAnimation(AnimationSequence^ animation);

	void StopAllAnimations();

	// start the animation
	void StartAnimation(String^ animationName);

	// stop the animation, reset animation sequence
	void StopAnimation(String^ animationName);

	// restart the animation from beginning
	// is stopanimation followed by startanimation
	void RestartAnimation(String^ animationName);

	void ClearAllAnimations();

	virtual void Update(float timeTotal, float timeDelta);

	void NotifyAnimationEvent(AnimationSequence^ seq, AnimationEvent event)
	{
		if (nullptr != AnimationEventHandler)
		{
			AnimationEventHandler(seq, event);
		}
	}

	property AnimationEventDelegate^ AnimationEventHandler
	{
		AnimationEventDelegate^ get()
		{
			return m_animationEventHandler;
		}

		void set(AnimationEventDelegate^ newDel)
		{
			m_animationEventHandler = newDel;
		}
	}

private:
	AnimationEventDelegate^ m_animationEventHandler;

	Vector<AnimationSequence ^>^ m_animationSequences;
	Vector<AnimationSequence ^>^ m_animationSequencesToStart;
};

}