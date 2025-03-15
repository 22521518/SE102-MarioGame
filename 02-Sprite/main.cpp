/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Mario.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_CAPPA 30
#define ID_TEX_DOOR 40

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario_transparent.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f

CCappa* cappa;
#define CAPPA_START_X 10.0f
#define CAPPA_START_Y 80.0f
#define CAPPA_START_VX 0.1f

CBrick *brick;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/

bool Collision(CGameObject* src, CGameObject* dest)
{
	float srcXMin = src->GetX();
	float srcXMax = src->GetX();
	float srcYMin = src->GetY();
	float srcYMax = src->GetX();

	float destXMin = dest->GetX();
	float destXMax = dest->GetX();
	float destYMin = dest->GetY();
	float destYMax = dest->GetX();

	return srcXMin < destXMax && srcXMax > srcXMin &&
		srcYMin < destYMax && srcYMax > srcYMin;
}

void LoadDoor()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	
	textures->Add(ID_TEX_DOOR, TEXTURE_PATH_ENEMIES);
	float height = 16, width = 16, gap = 2;
	sprites->Add(70001, 282, 99, 0, 0, textures->Get(ID_TEX_DOOR));
	sprites->Add(70002, 282, 99 + (height + gap) * 1, 298, 115 + (height + gap) * 1, textures->Get(ID_TEX_DOOR));
	sprites->Add(70003, 282, 99 + (height + gap) * 2, 298, 115 + (height + gap) * 2, textures->Get(ID_TEX_DOOR));
	sprites->Add(70004, 282, 99 + (height + gap) * 3, 298, 115 + (height + gap) * 3, textures->Get(ID_TEX_DOOR));
	sprites->Add(70005, 282, 99 + (height + gap) * 4, 298, 115 + (height + gap) * 4, textures->Get(ID_TEX_DOOR));
	sprites->Add(70006, 282, 99 + (height + gap) * 5, 298, 115 + (height + gap) * 5, textures->Get(ID_TEX_DOOR));
	sprites->Add(70007, 282, 99 + (height + gap) * 6, 298, 115 + (height + gap) * 6, textures->Get(ID_TEX_DOOR));
	sprites->Add(70008, 282, 99 + (height + gap) * 7, 298, 115 + (height + gap) * 7, textures->Get(ID_TEX_DOOR));

	LPANIMATION ani = new CAnimation(100);
	ani->Add({ 70001 , 7002});
	ani->Add({ 70003 , 7004});
	ani->Add({ 70005 , 7006});
	ani->Add({ 70007 , 7008});
	animations->Add(700, ani);
}

void LoadResources()
{
	LoadDoor();
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	//textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);
	textures->Add(ID_TEX_CAPPA, TEXTURE_PATH_ENEMIES);


	CSprites * sprites = CSprites::GetInstance();
	
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);
	LPTEXTURE texCappa = textures->Get(ID_TEX_CAPPA);

	// readline => id, left, top, right 
	// Mario
	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 200, 181, texMario);
	sprites->Add(10012, 155, 154, 171, 181, texMario);
	sprites->Add(10013, 125, 154, 141, 181, texMario);

	// Cappa
	// Left
	sprites->Add(20001, 6, 130, 21, 156, texCappa);
	sprites->Add(20002, 29, 130, 43, 156, texCappa);
	//Right
	sprites->Add(20011, 960 - 6 - 15, 130, 960 - 21 + 15, 156, texCappa);
	sprites->Add(20012, 960 - 29 - 16, 130, 960 - 43 + 15, 156, texCappa);

	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	// Mario
	//Right
	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(502, ani);

	//Left
	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(503, ani);

	// cappa
	ani = new CAnimation(100);
	ani->Add(20011);
	ani->Add(20012);
	animations->Add(600, ani);

	ani = new CAnimation(100);
	ani->Add(20001);
	ani->Add(20002);
	animations->Add(601, ani);

	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);

	int spriteHeight = 317 - 300;
	int gap = 2;
	int dis = spriteHeight + 2;
	
	//// gach
	//sprites->Add(20001 + dis, 300, 117 + dis, 317, 133 + dis, texMisc);
	//sprites->Add(20002 + dis, 318, 117 + dis, 335, 133 + dis, texMisc);
	//sprites->Add(20003 + dis, 336, 117 + dis, 353, 133 + dis, texMisc);
	//sprites->Add(20004 + dis, 354, 117 + dis, 371, 133 + dis, texMisc);

	// gach?
	sprites->Add(20001, 300, 117, 317, 133, texMisc);
	sprites->Add(20002, 318, 117, 335, 133, texMisc);
	sprites->Add(20003, 336, 117, 353, 133, texMisc);
	sprites->Add(20004, 354, 117, 371, 133, texMisc);

	ani = new CAnimation(100);
	ani->Add(20001,1000);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(510, ani);
	
/*	ani = new CAnimation(100);
	ani->Add(20001 + dis, 1000);
	ani->Add(20002 + dis);
	ani->Add(20003 + dis);
	ani->Add(20004 + dis);
	animations->Add(510 + dis, ani)*/;

	
	
	mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX);
	cappa = new CCappa(CAPPA_START_X, CAPPA_START_Y, CAPPA_START_VX);
	brick = new CBrick(100.0f, 100.0f);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
	if (cappa)
	cappa->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		brick->Render();
		mario->Render();
		if (cappa)
		cappa->Render();

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame *game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}