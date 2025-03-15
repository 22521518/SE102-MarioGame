#pragma once
#include "TankEnemy.h"
class CWhiteTankEnemy :
    public CTankEnemy
{
public:
	CWhiteTankEnemy() : CTankEnemy() {};
	CWhiteTankEnemy(float x, float y, float vx, float vy, LPTEXTURE* textures)
		: CTankEnemy(x, y, vx, vy, textures) {};

	virtual void OnCollision();
};

