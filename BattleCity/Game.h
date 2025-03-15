#pragma once
#include <vector>
#include <d3d10.h>
#include <d3dx10.h>
#include <Windows.h>

#include "GameObject.h"
#include "Texture.h"

#define BACKGROUND_COLOR D3DXCOLOR(0.f, 0.f, 0.f, 0.2f)

using namespace std;

class CGame
{
private:
	static CGame* __instance;
	CGame() { hWnd = NULL; };

	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state
	ID3DX10Sprite* spriteObject = NULL;				// Sprite handling object 

public:
	
	void Init(HWND hWnd);
	void LoadResources();
	void Update(DWORD dt);
	void CheckAllObjectCollision();
	void Render();

	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL);
	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b);
	LPTEXTURE LoadTexture(LPCWSTR texturePath);
	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }
	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }
	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	static CGame* GetInstance();
	~CGame();
};

