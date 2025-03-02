#pragma once
#include "CSprite.h"
class CGun : public CSprite
{
protected:

	LPCWSTR _textureBulletPath = L"bullet.png";

	float _bulletSpeed = 0.2f;
	float _bulletWidth = 12.0f;
	float _bulletHeight = 12.0f;
	bool _isFiring;
	bool _isBulletAlive;
	CSprite* _bulletSprite;
public:
	CGun(
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
	~CGun();
	void Update(DWORD dt, int backBufferWidth, int backBufferHeight) override;
	void Fire();
	void Render() override;
};

