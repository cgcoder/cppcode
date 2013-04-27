#include "pch.h"

#include "GameView.h"
#include "ViewController.h"

namespace GameEngine
{

ViewController::ViewController()
{
	m_currentViewName = nullptr;
	m_viewMap = ref new Map<String^, GameView^>();
}

ViewController::~ViewController()
{
	for_each(begin(m_viewMap),
		end(m_viewMap),
		[this](IKeyValuePair<String ^, GameView ^>^ keyValue)
	{
		GameView^ view = this->m_viewMap->Lookup(keyValue->Key);
		view->DisconnectRenderer();
	});

	m_viewMap->Clear();
	m_viewMap = nullptr;
}

void ViewController::Initialize(DirectXBase^ renderer)
{
	m_renderer = renderer;
}

void ViewController::AddView(String^ viewName, GameView^ gameView)
{
	m_viewMap->Insert(viewName, gameView);
	gameView->ConnectRenderer(m_renderer);
}

void ViewController::LoadViewResourceAsync()
{
	if (nullptr != m_currentViewName)
	{
		GameView^ view = m_viewMap->Lookup(m_currentViewName);
		view->State = ViewState::e_vsLoading;

		create_task([=]()
		{
			view->LoadResourceAsync();
		}, m_loadCancelToken.get_token()).then([=]()
		{
			view->State = ViewState::e_vsLoaded;
		});
	}
}

void ViewController::CancelLoadResource()
{
	m_loadCancelToken.cancel();
}

void ViewController::Update(float timeTotal, float timeDelta)
{
	if (m_currentViewName != nullptr)
	{
		m_viewMap->Lookup(m_currentViewName)->Update(timeTotal, timeDelta);
	}
}

void ViewController::Render()
{
	m_renderer->GetDC()->BeginDraw();
	m_renderer->GetDC()->Clear(ColorF(ColorF::Black));

	if (m_currentViewName != nullptr)
	{
		m_viewMap->Lookup(m_currentViewName)->Render();
	}

	m_renderer->GetDC()->EndDraw();
}

}