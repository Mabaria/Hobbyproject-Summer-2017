#include "D3D.h"

bool D3D::InitializeDevice()
{


	// create a struct to hold swap chain information
	DXGI_SWAP_CHAIN_DESC scd;

	// clear struct memory
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = this->mainWindow.getWindow();
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;
	scd.BufferDesc.RefreshRate.Denominator = 144;
	scd.BufferDesc.RefreshRate.Numerator = 1;

	// create device, devcon and swap chain using description
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&this->swapChain,
		&this->device,
		NULL,
		&this->devCon);

	if (FAILED(hr)) {
		MessageBoxA(NULL, "Error creating device and swapchain.", nullptr, MB_OK);
		exit(-1);
	}

	if (SUCCEEDED(hr)) {
		// get backbuffer address
		ID3D11Texture2D* pBackBuffer = nullptr;
		this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use address to create render target
		this->device->CreateRenderTargetView(pBackBuffer, NULL, &this->backBufferRTV);
		pBackBuffer->Release();
	}





	return SUCCEEDED(hr);
}



void D3D::CreateShaders() {

	// Creating default vertex shader
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		L"VertexShaderDefault.hlsl",
		nullptr,
		nullptr,
		"main",
		"vs_5_0",
		0,
		0,
		&pVS,
		nullptr
	);

	this->device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &this->vertexShaderDefault);

	// Create input layout for vertex shader
	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	this->device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->vertexLayout);
	pVS->Release();

	// Creating default pixel shader
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		L"PixelShaderDefault.hlsl",
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		0,
		0,
		&pPS,
		nullptr
	);

	this->device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &this->pixelShaderDefault);
}



D3D::D3D(HINSTANCE hInstance) : mainWindow(hInstance) {
	// Initialize the device and related swapchain / render target
	this->InitializeDevice();

	// Make sure the shaders are created and ready
	this->CreateShaders();

	this->mainViewPort.Width = this->mainWindow.getWidth();
	this->mainViewPort.Height = this->mainWindow.getHeight();
	this->mainViewPort.MinDepth = 0.0f;
	this->mainViewPort.MaxDepth = 1.0f;
	this->mainViewPort.TopLeftX = 0;
	this->mainViewPort.TopLeftY = 0;

}

D3D::~D3D() {
	if (this->swapChain != nullptr)
	{
		this->swapChain->Release();
		this->swapChain = nullptr;
	}
	if (this->backBufferRTV != nullptr)
	{
		this->backBufferRTV->Release();
		this->backBufferRTV = nullptr;
	}
	if (this->devCon)
	{
		this->devCon->ClearState();
	}
	if (this->device != nullptr)
	{
		this->device->Release();
		this->device = nullptr;
	}
	if (this->devCon != nullptr)
	{
		this->devCon->Release();
		this->devCon = nullptr;
	}
	this->vertexLayout->Release();
	this->vertexShaderDefault->Release();
	this->pixelShaderDefault->Release();
}

Window D3D::getWindowObject()
{
	return this->mainWindow;
}

ID3D11Device * D3D::getDevice() const
{
	return this->device;
}

ID3D11DeviceContext * D3D::getDevCon()
{
	return this->devCon;
}

IDXGISwapChain * D3D::getSwapChain() const
{
	return this->swapChain;
}

ID3D11RenderTargetView ** D3D::getBackBufferRTV()
{
	return &this->backBufferRTV;
}



