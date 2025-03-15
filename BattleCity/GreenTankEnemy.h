#pragma once
#include "TankEnemy.h"
class CGreenTankEnemy :
    public CTankEnemy
{
public:
	CGreenTankEnemy(float x, float y, float vx, float vy, LPTEXTURE* textures)
		: CTankEnemy(x, y, vx, vy, textures) {
	};
	virtual void OnCollision();
};

