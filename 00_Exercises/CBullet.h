#pragma once
#include "CSprite.h"
class CBullet :
    public CSprite
{
public:
	CBullet(
		ID3D10Device* pD3DDevice,
		ID3DX10Sprite* spriteObject,
		float x,
		float y,
		float vx,
		float vy,
		float width,
		float height,
		LPCWSTR texturePath
	);
	~CBullet();
	void Update(DWORD dt, int backBufferWidth, int backBufferHeight) override;
};

