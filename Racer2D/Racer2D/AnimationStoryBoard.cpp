#include "pch.h"

#include "AnimationSequence.h"
#include "AnimationStoryBoard.h"
#include "Animation.h"

AnimationStoryBoard::AnimationStoryBoard()
{
	m_animationSequences = ref new Vector<AnimationSequence ^>();
	m_animationSequencesToStart = ref new Vector<AnimationSequence ^>();
}

AnimationStoryBoard::~AnimationStoryBoard()
{
	m_animationSequences->Clear();
	m_animationSequences = nullptr;

	m_animationSequencesToStart->Clear();
	m_animationSequencesToStart = nullptr;
}

void AnimationStoryBoard::AddAnimation(AnimationSequence^ animationSeq)
{
	unsigned int index = 0;

	if (!m_animationSequences->IndexOf(animationSeq, &index))
	{
		m_animationSequences->Append(animationSeq);
	}
}

void AnimationStoryBoard::StopAllAnimations()
{
	for_each(begin(m_animationSequences),
		end(m_animationSequences),
		[&](AnimationSequence^ seq)
	{
		seq->ResetAndStop();
	});
}

void AnimationStoryBoard::StartAnimation(String^ animationName)
{
	unsigned int index = 0;

	for_each(begin(m_animationSequences),
		end(m_animationSequences),
		[&](AnimationSequence^ seq)
	{
		if (seq->Name->Equals(animationName))
		{
			if (!m_animationSequencesToStart->IndexOf(seq, &index))
			{
				seq->Start();
				m_animationSequencesToStart->Append(seq);
			}

			seq->Start();

			return;
		}
	});
	
}

void AnimationStoryBoard::StopAnimation(String^ animationName)
{
	unsigned int index = 0;

	for_each(begin(m_animationSequences),
		end(m_animationSequences),
		[&](AnimationSequence^ seq)
	{
		if (seq->Name->Equals(animationName))
		{
			if (m_animationSequencesToStart->IndexOf(seq, &index))
			{
				m_animationSequencesToStart->RemoveAt(index);
				return;
			}
		}
	});
}

void AnimationStoryBoard::RestartAnimation(String^ animationName)
{
	for_each(begin(m_animationSequences),
		end(m_animationSequences),
		[this, animationName](AnimationSequence^ seq)
	{
		if (seq->Name->Equals(animationName))
		{
			seq->Reset();
			this->StartAnimation(animationName);
			return;
		}
	});
}

void AnimationStoryBoard::ClearAllAnimations()
{
	m_animationSequences->Clear();
}

void AnimationStoryBoard::Update(float timeTotal, float timeDelta)
{
	Vector<AnimationSequence ^>^ seqToRemove = ref new Vector<AnimationSequence ^>();

	for_each(begin(m_animationSequencesToStart),
		end(m_animationSequencesToStart),
		[&](AnimationSequence^ seq)
	{
		seq->Update(timeTotal, timeDelta);

		if (seq->IsComplete)
		{
			NotifyAnimationEvent(seq, AnimationEvent::e_aeCompleted);
			seqToRemove->Append(seq);
		}
	});

	for_each(begin(seqToRemove),
		end(seqToRemove),
		[this](AnimationSequence^ seq)
	{
		unsigned int index = 0;

		if (m_animationSequencesToStart->IndexOf(seq, &index))
		{
			m_animationSequencesToStart->RemoveAt(index);
		}
	});
}