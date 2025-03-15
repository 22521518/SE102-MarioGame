#include "Tank.h"


CTank::CTank(float x, float y, float vx, float vy, LPTEXTURE textures[])
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	for (int i = 0; i < 4; i++)
	{
		textureList[i] = textures[i];
	}

	CGame* game = CGame::GetInstance();
	bulletTextureList[LEFT] = game->LoadTexture(BULLET_TEXTURE_PATH_LEFT);
	bulletTextureList[RIGHT] = game->LoadTexture(BULLET_TEXTURE_PATH_RIGHT);
	bulletTextureList[UP] = game->LoadTexture(BULLET_TEXTURE_PATH_UP);
	bulletTextureList[DOWN] = game->LoadTexture(BULLET_TEXTURE_PATH_DOWN);
}

void CTank::checkMove(float& v_x, float& v_y)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) 
	{
		v_x = -vx;
		dir = LEFT;
	}
	;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) 
	{
		v_x = vx;
		dir = RIGHT;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) 
	{
		v_y = -vy;
		dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) 
	{
		v_y = vy;
		dir = DOWN;
	}
}

void CTank::Update(DWORD dt)
{
	if (bullet != NULL)
	{
		bullet->Update(dt);

		CGame* game = CGame::GetInstance();
		HWND hWnd = game->GetWindowHandle();

		// Check if the bullet is out of the visible screen
		RECT rect;
		GetClientRect(hWnd, &rect);  // hWnd = window handle

		if (bullet->GetY() < 0 || bullet->GetY() > rect.bottom ||
			bullet->GetX() < 0 || bullet->GetX() > rect.right)
		{
			delete bullet;
			bullet = NULL;
		}
	}
}

void CTank::Fire()
{
	if (bullet != NULL)
	{
		return;
	}

	float vbullet_x = 0, vbullet_y = 0;
	switch (dir)
	{
	case LEFT:
		vbullet_x = -0.1f;
		break;
	case RIGHT:
		vbullet_x = 0.1f;
		break;
	case UP:
		vbullet_y = -0.1f;
		break;
	case DOWN:
		vbullet_y = 0.1f;
		break;
	}

	bullet = new CTankBullet(x, y, vbullet_x, vbullet_y, bulletTextureList[dir]);

}

void CTank::Render()
{
	texture = textureList[dir];
	CGame::GetInstance()->Draw(x, y, texture);

	if (bullet != NULL)
	{
		bullet->Render();
	}
}
