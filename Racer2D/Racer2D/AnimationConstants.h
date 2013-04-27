#pragma once

namespace GameEngine
{

#define POSITION 1
#define ROTATION 2
#define SCALE    3

public enum class AnimationMode : int
{
	e_amLoop,
	e_amStopAtEnd,
};

public enum class AnimationState : int
{
	e_asRunning,
	e_asNotRunning
};

public enum class AnimationEvent : int
{
	e_aeCompleted
};



}