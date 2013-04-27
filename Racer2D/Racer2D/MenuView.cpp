#include "pch.h"
#include "MenuView.h"
#include "AnimationStoryBoard.h"
#include "AnimationUtil.h"

namespace Racer2D
{

MenuView::MenuView()
{
	m_gameObject1 = ref new GameObject();
}

MenuView::~MenuView()
{
	m_gameObject1 = nullptr;
}

void MenuView::LoadResourceAsync()
{
	int i = 0;

	ComPtr<ID2D1Bitmap> pBitmap  = nullptr;

	x = 0;
	m_renderer->LoadBitmap(L"sparkle.png", &pBitmap);
	m_gameObject1->Bitmap = pBitmap.Get();
	/*
	m_gameObject1->StoryBoard->AddAnimation(AnimationUtil::CreateBackAndForthAnimationSequence(L"Animation1",
			m_gameObject1, 300, 0, 120));
	*/

	AnimationSequence^ seq = ref new AnimationSequence(L"rectangle");
	seq->AddAnimation(AnimationUtil::CreatePositionAnimation(L"left-right", m_gameObject1, 200, 0, 0, 50));
	seq->AddAnimation(AnimationUtil::CreatePositionAnimation(L"right-bottom", m_gameObject1, 0, 200, 51, 101));
	seq->AddAnimation(AnimationUtil::CreatePositionAnimation(L"right-left", m_gameObject1, -200, 0, 102, 152));
	seq->AddAnimation(AnimationUtil::CreatePositionAnimation(L"left-top", m_gameObject1, 0, -200, 153, 203));
	seq->Mode = AnimationMode::e_amLoop;
	m_gameObject1->StoryBoard->AddAnimation(seq);

	m_gameObject1->IsReady = true;
	m_gameObject1->StoryBoard->StartAnimation(L"rectangle");
}

void MenuView::Update(float totalTime, float elapsedTime)
{
	if (m_gameObject1->IsReady)
	{
		m_gameObject1->Update(totalTime, elapsedTime);
	}
}

void MenuView::Render()
{
	if (!this->IsLoaded)
	{
		return;
	}

	/*
	if (nullptr != m_pBitmap)
	{
		D2D1_SIZE_U size = m_pBitmap->GetPixelSize();

		m_renderer->GetDC()->DrawBitmap(m_pBitmap.Get(), D2D1::RectF(x++, 10, x + size.width, 10 + size.height));
	}
	*/

	if (m_gameObject1->IsReady)
	{
		m_gameObject1->Render(m_renderer);
	}
}		

/*
void MenuView::Render()
{
}

void MenuView::Update(float fElapsedTime, float fDeltaTime)
{
}

void MenuView::LoadResources()
{

}
*/

}