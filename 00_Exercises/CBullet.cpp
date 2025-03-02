#include "CBullet.h"
#include "debug.h"

CBullet::CBullet(
	ID3D10Device* pD3DDevice,
	ID3DX10Sprite* spriteObject,
	float x,
	float y,
	float vx,
	float vy,
	float width,
	float height,
	LPCWSTR texturePath
) : CSprite(pD3DDevice, spriteObject, x, y, vx, vy, width, height, texturePath)
{
}

CBullet::~CBullet()
{
}

void CBullet::Update(DWORD dt, int backBufferWidth, int backBufferHeight)
{
	_y += _vy * dt;
}