#include "D3D12Lite.h"

using namespace D3D12Lite;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
		else
		{
			return DefWindowProc(hwnd, uMessage, wParam, lParam);
		}
	case WM_DESTROY:
		[[fallthrough]];
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, uMessage, wParam, lParam);
	}
}

int main()
{
	std::wstring applicationName = L"D3D12 Tutorial";
	Uint2 windowSize = { 1920,1080 };
	HINSTANCE moduleHandle = GetModuleHandle(nullptr);

	WNDCLASSEX wcex =
	{
		.cbSize = static_cast<UINT>(sizeof(WNDCLASSEX)),
		.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		.lpfnWndProc = WindowProc,
		.hInstance = moduleHandle,
		.hIcon = LoadIcon(nullptr, IDI_WINLOGO),
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
		.lpszMenuName = nullptr,
		.lpszClassName = applicationName.c_str(),
	};
	wcex.hIconSm = wcex.hIcon;

	if (!RegisterClassEx(&wcex))
	{
		DWORD dwError = GetLastError();

		MessageBox(
			nullptr,
			L"Call to RegisterClassEx failed!",
			L"D3D12 Tutorial",
			NULL
		);

		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
		{
			return HRESULT_FROM_WIN32(dwError);
		}

		return E_FAIL;
	}

	HWND windowHandle = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		applicationName.c_str(),
		applicationName.c_str(),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_SIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) - windowSize.x) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - windowSize.y) / 2,
		windowSize.x,
		windowSize.y,
		nullptr,
		nullptr,
		moduleHandle,
		nullptr
	);

	if (!windowHandle)
	{
		DWORD dwError = GetLastError();

		MessageBox(
			nullptr,
			L"Call to CreateWindowEx failed!",
			L"D3D12 Tutorial",
			NULL
		);

		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
		{
			return HRESULT_FROM_WIN32(dwError);
		}

		return E_FAIL;
	}

	ShowWindow(windowHandle, SW_SHOW);
	SetForegroundWindow(windowHandle);
	SetFocus(windowHandle);
	ShowCursor(TRUE);

	BOOL shouldExit = FALSE;
	while (!shouldExit)
	{
		MSG msg{ 0 };
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			shouldExit = TRUE;
		}
	}

	DestroyWindow(windowHandle);
	windowHandle = nullptr;

	UnregisterClass(applicationName.c_str(), moduleHandle);
	moduleHandle = nullptr;

	return 0;
}