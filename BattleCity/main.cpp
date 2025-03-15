#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectPool.h"
#include "WindowSetUp.h"

#include "MyTank.h"
#include "GreenTankEnemy.h"
#include "WhiteTankEnemy.h"
#include "RedTankEnemy.h"

#define MAX_FRAME_RATE 60

#define WINDOW_CLASS_NAME L"Game Window"
#define MAIN_WINDOW_TITLE L"Battle City"
#define WINDOW_ICON_PATH L"brick.ico"

#define BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 400

using namespace std;


int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	LPTEXTURE* tex = CGameObjectPool::GetInstance()->GetMyTankTex();
	float posY = SCREEN_HEIGHT - tex[0]->getHeight() / 2;
	float posX = rand() % SCREEN_WIDTH + tex[0]->getWidth() / 2;
	LPGAMEOBJECTMOVABLE myTank = new CMyTank(posX, posY, 0.1f, 0.1f, CGameObjectPool::GetInstance()->GetMyTankTex(), done);
	CGameObjectPool::GetInstance()->AddActiveObject(myTank);

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
			CGame::GetInstance()->Update((DWORD)dt);
			CGame::GetInstance()->CheckAllObjectCollision();
			CGame::GetInstance()->Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

bool checkNext(vector<int> arr, int size, int index) {
	if (index < 0 || index >= size) return false;
	if (arr[index] == 1) return true;
	if (index == size - 1 || arr[index] == 0 && arr[index - 1] == 1) return true;
	if (index == 0 || arr[index] == 0 && arr[index + 1] == 1) return true;
	return false;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_ICON_PATH, WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE);
	if (hWnd == NULL) {
		DebugOut(L"[ERROR] Failed to create game window!\n");
		return 0;
	}
	else {
		DebugOut(L"[INFO] Game window created successfully!\n");
	}
	CGame::GetInstance()->Init(hWnd);
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	CGame::GetInstance()->LoadResources();

	int numSlots = SCREEN_WIDTH / CGameObjectPool::GetInstance()->GetGreenEnemyTex()[0]->getWidth();
	vector<int> availableSlots(numSlots * 2);
	for (int i = 0; i < numSlots; i+=2) {
		availableSlots[i] = 0;
	}

	for (int i = 0; i < 7; i++) {
		int randomX = rand() % 3;
		LPTEXTURE* tex;
		float randomSlot = rand() % numSlots;
		while (checkNext(availableSlots, numSlots, randomSlot)) {
			randomSlot = rand() % numSlots;
		}
		float posY = 0, posX = 0;

		switch (randomX) {
		case 0:
			tex = CGameObjectPool::GetInstance()->GetGreenEnemyTex();
			posY = tex[0]->getHeight() / 2;
			posX = tex[0]->getWidth() * randomSlot + tex[0]->getWidth();
			availableSlots[randomSlot] = 1;
			CGameObjectPool::GetInstance()->AddActiveObject(new CGreenTankEnemy(posX, posY, 0.1f, 0.1f, CGameObjectPool::GetInstance()->GetGreenEnemyTex()));
			break;
		case 1:
			tex = CGameObjectPool::GetInstance()->GetWhiteEnemyTex();
			posY = tex[0]->getHeight() / 2;
			posX = tex[0]->getWidth() * randomSlot + tex[0]->getWidth();
			availableSlots[randomSlot] = 1;
			CGameObjectPool::GetInstance()->AddActiveObject(new CWhiteTankEnemy(posX, posY, 0.1f, 0.1f, CGameObjectPool::GetInstance()->GetWhiteEnemyTex()));
			break;
		case 2:
			tex = CGameObjectPool::GetInstance()->GetRedEnemyTex();
			posY = tex[0]->getHeight() / 2;
			posX = tex[0]->getWidth() * randomSlot + tex[0]->getWidth();
			availableSlots[randomSlot] = 1;
			CGameObjectPool::GetInstance()->AddActiveObject(new CRedTankEnemy(posX, posY, 0.1f, 0.1f, CGameObjectPool::GetInstance()->GetRedEnemyTex()));
			break;
		default:
			break;
		}
	}


	Run();

	return 0;
}