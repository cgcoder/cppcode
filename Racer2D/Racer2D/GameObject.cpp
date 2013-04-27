#include "pch.h"

#include "GameObject.h"
#include "AnimationStoryBoard.h"

namespace GameEngine
{

GameObject::GameObject()
{
	m_position = Point2F(0, 0);
	m_transformationMatrix = Matrix3x2F::Identity();
	m_width = 0;
	m_height = 0;
	m_scale = 1.0f;
	m_rotation = 0;
	m_originalHeight = 0;
	m_originalWidth = 0;
	m_updatables = ref new Vector<IUpdatable ^>();
}

GameObject::~GameObject()
{
	if (nullptr != m_updatables)
	{
		m_updatables->Clear();
		m_updatables = nullptr;
	}

	m_pBitmap = nullptr;
}

AnimationStoryBoard^ GameObject::StoryBoard::get()
{
	if (nullptr == m_storyBoard)
	{
		m_storyBoard = ref new AnimationStoryBoard();
		m_updatables->Append(m_storyBoard);
	}
	return m_storyBoard;
}

void GameObject::Update(float timeTotal, float timeDelta)
{
	UpdateTransformationMatrix();

	for_each(begin(m_updatables),
		end(m_updatables),
		[=](IUpdatable^ updatable)
	{
		updatable->Update(timeTotal, timeDelta);
	});
}

void GameObject::Render(DirectXBase^ renderer)
{
	if (nullptr != m_pBitmap)
	{
		renderer->GetDC()->SetTransform(m_transformationMatrix);
		renderer->GetDC()->DrawBitmap(m_pBitmap.Get());
	}
}

void GameObject::UpdateTransformationMatrix()
{
	m_width = m_originalWidth * m_scale;
	m_height = m_originalHeight * m_scale;

	m_transformationMatrix = Matrix3x2F::Scale(m_scale, m_scale) *
					Matrix3x2F::Rotation(
						m_rotation, 
						Point2F(m_width / 2, m_height / 2)) *
					Matrix3x2F::Translation(
						m_position.x, 
						m_position.y);

}

};