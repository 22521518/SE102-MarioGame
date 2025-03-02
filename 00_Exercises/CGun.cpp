#include "CGun.h"
#include "CBullet.h"
#include "debug.h"
#include <iostream>
#include <memory>

CGun::CGun(
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
	_isFiring = false;
	_isBulletAlive = false;
}

CGun::~CGun()
{
	if (_bulletSprite)
	{
		delete _bulletSprite;
		_bulletSprite = NULL;
	}
}

void CGun::Render()
{
	CSprite::Render();
	if (_bulletSprite)
	{
		_bulletSprite->Render();
	}
}

void CGun::Update(DWORD dt, int backBufferWidth, int backBufferHeight)
{
    float rightEdge = backBufferWidth;
    float speed = _vx * dt; // Speed factor

    // Movement with boundary checks
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		_x = max(0, _x - speed);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
        _x = min(rightEdge, _x + speed);
	}

    // Shooting mechanic
    if ((GetKeyState(VK_SPACE) & 0x8000) && !_bulletSprite)
    {
        Fire();
    }

	if (_bulletSprite)
	{
		_bulletSprite->Update(dt, backBufferWidth, backBufferHeight);

		if (_bulletSprite->GetY() > backBufferHeight)
		{
			delete _bulletSprite;
			_bulletSprite = NULL;
		}
	}
}

void CGun::Fire()
{
	if (!_bulletSprite)
	{
		_bulletSprite = new CBullet(_pD3DDevice, _spriteObject, _x, _y, 0, 0.2f, _bulletWidth, _bulletHeight, _textureBulletPath);
		_bulletSprite->LoadResource();
	}
}