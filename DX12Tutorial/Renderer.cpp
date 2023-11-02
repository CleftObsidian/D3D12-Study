#include "Renderer.h"

Renderer::Renderer(HWND windowHandle, Uint2 screenSize)
	: mDevice(std::make_unique<Device>(windowHandle, screenSize))
	, mGraphicsContext(mDevice->CreateGraphicsContext())
{
}

Renderer::~Renderer()
{
	mDevice->WaitForIdle();
	mDevice->DestroyContext(std::move(mGraphicsContext));
	mDevice = nullptr;
}

void Renderer::RenderClearColorTutorial()
{
	mDevice->BeginFrame();

	TextureResource& backBuffer = mDevice->GetCurrentBackBuffer();

	mGraphicsContext->Reset();

	mGraphicsContext->AddBarrier(backBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET);
	mGraphicsContext->FlushBarriers();

	mGraphicsContext->ClearRenderTarget(backBuffer, Color(0.3f, 0.3f, 0.8f));

	mGraphicsContext->AddBarrier(backBuffer, D3D12_RESOURCE_STATE_PRESENT);
	mGraphicsContext->FlushBarriers();

	mDevice->SubmitContextWork(*mGraphicsContext);

	mDevice->EndFrame();
	mDevice->Present();
}

void Renderer::Render()
{
	RenderClearColorTutorial();
}
