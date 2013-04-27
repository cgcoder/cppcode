#include "pch.h"

#include "AnimationUtil.h"

#include "AnimationSequence.h"
#include "MoveAnimation.h"

namespace GameEngine
{

Animation^ AnimationUtil::CreatePositionAnimation(String^ name, GameObject^ object, float deltaX, float deltaY, int startFrame, int endFrame)
{
	MoveAnimation^ animation = ref new MoveAnimation(name, object, deltaX, deltaY, startFrame, endFrame);
	return animation;
}

AnimationSequence^ AnimationUtil::CreateBackAndForthAnimationSequence(String^ name, GameObject^ object, float deltaX, float deltaY, int frames)
{
	AnimationSequence^ seq = ref new AnimationSequence(name);

	int onewayStartFrame = 0;
	int onewayEndFrame = onewayStartFrame + frames;

	int otherwayStartFrame = onewayEndFrame + 1;
	int otherWayEndFrame = otherwayStartFrame + frames;

	MoveAnimation^ onewayAnimation = ref new MoveAnimation(name + "1", object, deltaX, deltaY, onewayStartFrame, onewayEndFrame);
	MoveAnimation^ otherwayAnimation = ref new MoveAnimation(name + "2", object, -deltaX, -deltaY, otherwayStartFrame, otherWayEndFrame);

	seq->AddAnimation(onewayAnimation);
	seq->AddAnimation(otherwayAnimation);

	seq->Mode = AnimationMode::e_amLoop;

	return seq;
}

};