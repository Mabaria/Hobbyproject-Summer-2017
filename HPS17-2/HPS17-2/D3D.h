#ifndef D3D_H
#define D3D_H
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include <windows.h>
#include <windowsx.h>
#include "Window.h"



class D3D {
private:
	Window mainWindow;
	D3D11_VIEWPORT mainViewPort;

	ID3D11Device* device;
	ID3D11DeviceContext* devCon;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferRTV;

	ID3D11InputLayout* vertexLayout = nullptr;
	ID3D11VertexShader* vertexShaderDefault = nullptr;
	ID3D11PixelShader* pixelShaderDefault = nullptr;
	bool InitializeDevice();
	void CreateShaders();



public:
	D3D(HINSTANCE hInstance);
	~D3D();

	Window getWindowObject();
	ID3D11Device* getDevice() const;
	ID3D11DeviceContext* getDevCon();
	IDXGISwapChain* getSwapChain() const;
	ID3D11RenderTargetView** getBackBufferRTV();




};




#endif