#pragma once
#include <collection.h>
#include <ppltasks.h>

#include "DirectXHelper.h"
#include "DirectXRenderer.h"
#include "DirectXBase.h"

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

ref class GameView;

using namespace concurrency;
using namespace std;

namespace GameEngine
{

ref class ViewController
{
internal:
	ViewController();

public:
	virtual ~ViewController();

	virtual void Initialize(DirectXBase^ renderer);

	void AddView(String^ viewName, GameView^ gameView);

	property String^ CurrentViewName
	{
		String^ get()
		{
			return m_currentViewName;
		}

		void set(String^ currentView)
		{
			if (m_viewMap->HasKey(currentView))
			{
				GameView^ oldView = nullptr == m_currentViewName ? 
									nullptr: 
									m_viewMap->Lookup(m_currentViewName);

				m_currentViewName = currentView;

				if (nullptr != oldView)
				{
					oldView->OnDeActivate();
				}

				GameView^ newView = m_viewMap->Lookup(m_currentViewName);
				LoadViewResourceAsync();
				newView->OnActivate(oldView);
			}
			else
			{
				throw ref new Platform::Exception(E_UNEXPECTED, L"View not found!");
			}
		}
	}

	property DirectXBase^ Renderer
	{
		DirectXBase^ get()
		{
			return m_renderer;
		}
	}

	void Update(float timeTotal, float timeDelta);

	void Render();

	void LoadViewResourceAsync();

	void CancelLoadResource();

private:
	String^ m_currentViewName;
	Map<String ^, GameView ^>^ m_viewMap;

	cancellation_token_source m_loadCancelToken;
	DirectXBase^ m_renderer;

};

}