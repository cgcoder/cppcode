#pragma once

#include "pch.h"

#include <collection.h>

#include "GameObject.h"
#include "DirectXHelper.h"
#include "DirectXRenderer.h"
#include "DirectXBase.h"

using namespace DirectX;
using namespace D2D1;
using namespace Platform::Collections;
using namespace Microsoft::WRL;
using namespace Windows::Foundation::Collections;

namespace GameEngine
{

ref class ViewController;

public enum class ViewState : int
{
	e_vsLoading,
	e_vsLoaded,
};

ref class GameView abstract
{
internal:
	GameView();

public:
	virtual ~GameView();

	void ConnectRenderer(DirectXBase^ pRenderer);
	void DisconnectRenderer();

	virtual void OnAdd(ViewController^ controller);
	virtual void OnRemove();

	virtual void Render();
	virtual void Update(float totalTime, float elapsedTime);

	virtual void OnActivate(GameView^ previousView);
	virtual void OnDeActivate();
	virtual void LoadResourceAsync();

	property ViewState State
	{
		ViewState get()
		{
			return m_viewState;
		}

		void set(ViewState viewState)
		{
			m_viewState = viewState;
		}
	}

	property bool IsLoaded
	{
		bool get()
		{
			return ViewState::e_vsLoaded == m_viewState;
		}
	}

protected private:
	DirectXBase^ m_renderer;
	ViewController^ m_controller;

	ViewState m_viewState;
	Vector<GameObject ^>^ m_gameObjects;
	Vector<GameObject ^>^ m_gameObjectsToDelete;
private:
};

}