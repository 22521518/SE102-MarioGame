#pragma once

#include "Game.h"
#include "GameObjectPool.h"
#include "GameObjectMovable.h"
#include "Bullet.h"
#include "TexturePath.h"

class CTank :
    public CGameObjectMovable
{
protected:
	CBullet* bullet = NULL;
	float bulletSpeed = 0.2f;

	float GetBulletSpeed() { return bulletSpeed; }
public:
	CTank();
	CTank(float x, float y, float vx, float vy, LPTEXTURE* textures);
	CTank(CTank* obj);

	virtual void OnCollision() = 0;
	virtual void UpdateVelocity(float& vx, float& vy) = 0;
	virtual void Fire();
};

