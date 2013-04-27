#include "pch.h"
#include <d2d1helper.h>
#include "DirectXRenderer.h"
#include "MenuView.h"

using namespace DirectX;
using namespace D2D1;
using namespace Microsoft::WRL;
using namespace Windows::Foundation::Collections;

DirectXRenderer::DirectXRenderer()
{
}

void DirectXRenderer::CreateDeviceIndependentResources()
{
	DirectXBase::CreateDeviceIndependentResources();
	m_pView = nullptr; //ref new MenuView();
}

void DirectXRenderer::CreateDeviceResources()
{
	DirectXBase::CreateDeviceResources();
}

void DirectXRenderer::CreateWindowSizeDependentResources()
{
	DirectXBase::CreateWindowSizeDependentResources();
}

void DirectXRenderer::Render()
{
	
}

void DirectXRenderer::SaveInternalState(IPropertySet^ state)
{
	
}

void DirectXRenderer::LoadInternalState(IPropertySet^ state)
{
	
}
