#include "Window.h"

Window::Window(HINSTANCE instance) : hInstance(instance) {
	this->window = nullptr;
	this->hInstance = GetModuleHandle(0);
	this->windowTitle = "Hobbyproject Summer 2017 - Rikard Magnom";
	this->width = 1280;
	this->height = 720;

	this->Initialize();
}

Window::~Window() {

}

LRESULT	CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (msg)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


bool Window::Initialize() {
	bool result = true;

	WNDCLASSEX wc;

	// Clear window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill window struct with info
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = this->WindowProc;
	wc.hInstance = this->hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	// Register the window class
	RegisterClassEx(&wc);

	// AdjustWindowRect uses the desired client size (RECT wr) to specify the required window size


	RECT wr = { 0, 0, this->width, this->height };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

														  // create the window and use the result as the handle
	this->window = CreateWindowEx(NULL,
		"WindowClass1",    // name of the window class
		this->windowTitle,   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		0,    // x-position of the window
		0,    // y-position of the window
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		this->hInstance,    // application handle
		NULL);    // used with multiple windows, NULL


	return result;
}

HWND Window::getWindow() const
{
	return this->window;
}

int Window::getHeight() const
{
	return this->height;
}

int Window::getWidth() const
{
	return this->width;
}