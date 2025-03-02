#include "Ship.h"
#include "Game.h"

#define SHIP_HEIGHT 38.0f
#define SHIP_WIDTH 25.0f

void CShip::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0)
	{
		x = 0;
	}
	else if (x >= BackBufferWidth - texture->getWidth())
	{
		x = (float)(BackBufferWidth - texture->getWidth());
	}
	if (y <= 0 || y >= CGame::GetInstance()->GetBackBufferHeight() - texture->getHeight())
	{
		x = getRandomFloat(0, (float)(CGame::GetInstance()->GetBackBufferHeight() - texture->getHeight()));
		y = 0;
	}
}