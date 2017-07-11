#ifndef D3D_H
#define D3D_H
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include <windows.h>
#include <windowsx.h>


class D3D {
private:
	ID3D11Device* device;
	ID3D11DeviceContext* devCon;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferRTV;




public:
	D3D();
	~D3D();

	ID3D11Device* getDevice() const;
	ID3D11DeviceContext* getDevCon();
	IDXGISwapChain* getSwapChain() const;
	ID3D11RenderTargetView** getBackBufferRTV();

	bool Initialize(HWND window);


};




#endif