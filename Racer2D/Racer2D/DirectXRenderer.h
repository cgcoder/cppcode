#pragma once

#include "DirectXBase.h"
#include "GameView.h"

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;

using namespace GameEngine;

namespace GameEngine
{

ref class DirectXRenderer sealed : public DirectXBase
{
public :
	DirectXRenderer();

	// DirectXBase methods.
	virtual void CreateDeviceIndependentResources() override;
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;

	// Methods to save and load state in response to suspend.
	void SaveInternalState(Windows::Foundation::Collections::IPropertySet^ state);
	void LoadInternalState(Windows::Foundation::Collections::IPropertySet^ state);

protected private:
	GameView^ m_pView;
	DirectXRenderer^ m_pRenderer;
};

}