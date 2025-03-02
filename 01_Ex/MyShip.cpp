#include "MyShip.h"
#include <iostream>
#include <memory>

#include "debug.h"
#include "Game.h"

using namespace std;

void CMyShip::Input(float& v_x, float& v_y)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) v_x = -vx;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) v_x = vx;
	if (GetAsyncKeyState(VK_UP) & 0x8000) v_y = -vy;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) v_y = vy;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) Fire();
}

void CMyShip::RemoveBullet()
{
	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[](CBullet* bullet) {
				if (bullet->GetY() < 0) {
					delete bullet;  // Free memory if using raw pointers
					return true;    // Mark for removal
				}
				return false;
			}),
		bullets.end());

}

void CMyShip::Update(DWORD dt)
{
	float v_x = 0, v_y = 0;
	Input(v_x, v_y);

	x += v_x * dt;
	y += v_y * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0)
	{
		x = 0;
	}
	else if (x >= BackBufferWidth - texture->getWidth())
	{
		x = (float)(BackBufferWidth - texture->getWidth());
	}
	if (y <= 0)
	{
		y = 0;
	}
	else if (y >= CGame::GetInstance()->GetBackBufferHeight() - texture->getHeight())
	{
		y = (float)(CGame::GetInstance()->GetBackBufferHeight() - texture->getHeight());
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt);
	}	
	RemoveBullet();
}


void CMyShip::Fire()
{
	CBullet* bullet = new CBullet(x, y, -0.2f, CGame::GetInstance()->LoadTexture(L"bullet.png"));
	bullets.push_back(bullet);
}