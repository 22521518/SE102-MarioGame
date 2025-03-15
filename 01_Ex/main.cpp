	/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 01 - SKELETON CODE 

	This sample illustrates how to:

	1/ Re-organize introductory code to an initial skeleton for better scalability
	2/ CGame is a singleton, playing a role of an "engine".
	3/ CGameObject is an abstract class for all game objects
	4/ CTexture is a wrapper class for ID3D10TEXTURE 
	
	NOTE: to create transparent background, download GIMP, then use Color to Alpha feature 
================================================================ */

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>
#include <random>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Tank.h"

#define WINDOW_CLASS_NAME L"Game Window"
#define MAIN_WINDOW_TITLE L"01 - Skeleton"
#define WINDOW_ICON_PATH L"brick.ico"

#define TEXTURE_PATH_BRICK L"brick.png"
#define TEXTURE_PATH_MARIO L"mario.png"

#define TEXTURE_PATH_TANK_TOP L"tank/top.png"
#define TEXTURE_PATH_TANK_BOTTOM L"tank/bottom.png"
#define TEXTURE_PATH_TANK_LEFT L"tank/left.png"
#define TEXTURE_PATH_TANK_RIGHT L"tank/right.png"

#define TEXTURE_PATH_ENEMY_GREEN_RIGHT L"enemy/green/right.png"
#define TEXTURE_PATH_ENEMY_GREEN_LEFT L"enemy/green/left.png"
#define TEXTURE_PATH_ENEMY_GREEN_TOP L"enemy/green/top.png"
#define TEXTURE_PATH_ENEMY_GREEN_BOTTOM L"enemy/green/bottom.png"

#define TEXTURE_PATH_ENEMY_WHITE_RIGHT L"enemy/white/right.png"
#define TEXTURE_PATH_ENEMY_WHITE_LEFT L"enemy/white/left.png"
#define TEXTURE_PATH_ENEMY_WHITE_TOP L"enemy/white/top.png"
#define TEXTURE_PATH_ENEMY_WHITE_BOTTOM L"enemy/white/bottom.png"

#define TEXTURE_PATH_ENEMY_RED_RIGHT L"enemy/red/right.png"
#define TEXTURE_PATH_ENEMY_RED_LEFT L"enemy/red/left.png"
#define TEXTURE_PATH_ENEMY_RED_TOP L"enemy/red/top.png"
#define TEXTURE_PATH_ENEMY_RED_BOTTOM L"enemy/red/bottom.png"

#define TEXTURE_PATH_MISC L"misc.png"

#define BACKGROUND_COLOR D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240


using namespace std;

vector<LPGAMEOBJECT> objects;

#define SHIP_START_X SCREEN_WIDTH / 2
#define SHIP_START_Y SCREEN_HEIGHT - 100


LPTEXTURE* myTankTex = new LPTEXTURE[4];
LPTEXTURE* greenEnemyTex = new LPTEXTURE[4];
LPTEXTURE* whiteEnemyTex = new LPTEXTURE[4];
LPTEXTURE* redEnemyTex = new LPTEXTURE[4];

CTank* myTank;

// Global key state
bool keys[256] = { false };

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_KEYDOWN:  // Key pressed
		keys[wParam] = true;
		break;

	case WM_KEYUP:  // Key released
		keys[wParam] = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources. In this example, create a brick object and mario object
*/

float getRandomFloat(float min, float max) {
	static std::random_device rd;  // Random seed
	static std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<float> dist(min, max); // Range

	return dist(gen);
}

void LoadResources()
{
	CGame * game = CGame::GetInstance();

	myTankTex[0] = game->LoadTexture(TEXTURE_PATH_TANK_TOP);
	myTankTex[1] = game->LoadTexture(TEXTURE_PATH_TANK_BOTTOM);
	myTankTex[2] = game->LoadTexture(TEXTURE_PATH_TANK_LEFT);
	myTankTex[3] = game->LoadTexture(TEXTURE_PATH_TANK_RIGHT);

	greenEnemyTex[0] = game->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_TOP);
	greenEnemyTex[1] = game->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_BOTTOM);
	greenEnemyTex[2] = game->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_LEFT);
	greenEnemyTex[3] = game->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_RIGHT);

	whiteEnemyTex[0] = game->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_TOP);
	whiteEnemyTex[1] = game->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_BOTTOM);
	whiteEnemyTex[2] = game->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_LEFT);
	whiteEnemyTex[3] = game->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_RIGHT);

	redEnemyTex[0] = game->LoadTexture(TEXTURE_PATH_ENEMY_RED_TOP);
	redEnemyTex[1] = game->LoadTexture(TEXTURE_PATH_ENEMY_RED_BOTTOM);
	redEnemyTex[2] = game->LoadTexture(TEXTURE_PATH_ENEMY_RED_LEFT);
	redEnemyTex[3] = game->LoadTexture(TEXTURE_PATH_ENEMY_RED_RIGHT);


	//mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX, MARIO_START_VY, texMario);
	myTank = new CTank(100, 100 , 0.1f, 0.1f, myTankTex);
	objects.push_back(myTank);
	for (int i = 0; i < 8; i++)
	{
		int ran = rand() % 3;
		LPTEXTURE* enemy = NULL;
		switch (ran)
		{
		case 0:
			enemy = greenEnemyTex;
			break;
		case 1:
			enemy = whiteEnemyTex;
			break;
		case 2:
			enemy = redEnemyTex;
			break;
		}

		objects.push_back(new CTank(getRandomFloat(0, SCREEN_WIDTH), getRandomFloat(0, SCREEN_HEIGHT), 0.0f, 0.1f, enemy));
	}

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	/*
	for (int i=0;i<n;i++)
		objects[i]->Update(dt);
	*/

	for (int i = 0; i < objects.size(); i++)
	{
		(objects[i])->Update(dt);
	}

}

/*
	Render a frame 
*/
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

		for (int i = 0; i < objects.size(); i++)
		{
			(objects[i])->Render();
		}

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 317, 134);
		//g->Draw(10, 10, texMario, 215, 120, 234, 137);

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
) 
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame * game = CGame::GetInstance();
	game->Init(hWnd);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);


	LoadResources();

	Run();

	return 0;
}