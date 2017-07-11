#ifndef WINDOW_H
#define WINDOW_H
#include <windows.h>    
#include <windowsx.h>
#include <string>

class Window {
private:
	HWND window;
	HINSTANCE hInstance;
	int height;
	int width;
	LPCSTR windowTitle;


public:
	Window(HINSTANCE instance);
	~Window();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Initialize();

	HWND getWindow() const;
	int getHeight() const;
	int getWidth() const;
};




#endif