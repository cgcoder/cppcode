#include "pch.h"
#include "GameView.h"

namespace GameEngine
{

GameView::GameView() :
	m_renderer(nullptr),
	m_controller(nullptr)
{
	m_gameObjects = ref new Vector<GameObject ^>();
	m_gameObjectsToDelete = ref new Vector<GameObject ^>();
}

GameView::~GameView()
{
	m_gameObjects->Clear();
	m_gameObjects = nullptr;

	m_gameObjectsToDelete->Clear();
	m_gameObjectsToDelete = nullptr;
}

void GameView::ConnectRenderer(DirectXBase^ pRenderer)
{
	m_renderer = pRenderer;
}

void GameView::DisconnectRenderer()
{
	m_renderer = nullptr;
}

void GameView::OnAdd(ViewController^ controller)
{
	m_controller = controller;
}

void GameView::Render()
{
}

void GameView::Update(float totalTime, float timeDelta)
{
	unsigned int index = 0;

	for_each(begin(m_gameObjects),
		end(m_gameObjects),
		[&](GameObject^ object)
	{
		object->Update(totalTime, timeDelta);

		if (object->MarkedForDelete)
		{
			m_gameObjectsToDelete->Append(object);
		}
	});

	for_each(begin(m_gameObjectsToDelete),
		end(m_gameObjectsToDelete),
		[&](GameObject^ object)
	{
		if (m_gameObjects->IndexOf(object, &index))
		{
			m_gameObjects->RemoveAt(index);
		}
	});

	m_gameObjectsToDelete->Clear();
}

void GameView::OnRemove()
{
	m_controller = nullptr;
}

void GameView::OnActivate(GameView^ previousView)
{
	
}

void GameView::OnDeActivate()
{
	
}

// called from different thread.. perform longer task here..
void GameView::LoadResourceAsync()
{

}

}