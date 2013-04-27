#pragma once

#include "GameView.h"
#include "GameObject.h"

using namespace GameEngine;

namespace Racer2D
{

ref class MenuView sealed : public GameEngine::GameView
{
internal:
	MenuView();

public:
	virtual ~MenuView();
	virtual void LoadResourceAsync() override;
	virtual void Render() override;
	virtual void Update(float totalTime, float elapsedTime) override;

private:
	GameObject^ m_gameObject1;

	float x;
};

}