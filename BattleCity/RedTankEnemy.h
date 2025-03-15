#pragma once
#include "TankEnemy.h"
class CRedTankEnemy :
    public CTankEnemy
{
public:
	CRedTankEnemy(float x, float y, float vx, float vy, LPTEXTURE* textures)
		: CTankEnemy(x, y, vx, vy, textures) {
	};
	virtual void OnCollision();
};

