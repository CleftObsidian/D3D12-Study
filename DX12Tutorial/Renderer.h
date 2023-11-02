#pragma once
#include "D3D12Lite.h"

using namespace D3D12Lite;

class Renderer final
{
public:
	Renderer(HWND windowHandle, Uint2 screenSize);
	Renderer(const Renderer& other) = delete;
	Renderer(Renderer&& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer& operator=(Renderer&& other) = delete;
	~Renderer();

	void RenderClearColorTutorial();
	void Render();

private:
	std::unique_ptr<Device> mDevice;
	std::unique_ptr<GraphicsContext> mGraphicsContext;
};