#pragma once

#include <collection.h>

#include "IUpdatable.h"
#include "Animation.h"
#include "GameObject.h"
#include "AnimationSequence.h"

using namespace Platform;
using namespace Microsoft::WRL;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace GameEngine
{

ref class AnimationUtil
{
internal:
	static Animation^ CreatePositionAnimation(String^ name, GameObject^ object, float deltaX, float deltaY, int startFrame, int endFrame);
	static AnimationSequence^ CreateBackAndForthAnimationSequence(String^ name, GameObject^ object, float deltaX, float deltaY, int frames);
};

}