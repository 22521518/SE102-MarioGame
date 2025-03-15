#pragma once
#include "Tank.h"
#include "debug.h"
class CTankEnemy :
	public CTank
{
protected:
	int m_timeToChangeDirection = 25;
	EDIRECTION m_direction = DOWN;
public:
	CTankEnemy(): CTank() {};
	CTankEnemy(float x, float y, float vx, float vy, LPTEXTURE* textures)
		: CTank(x, y, vx, vy, textures) {};

	virtual void OnCollision() = 0;
	virtual void UpdateVelocity(float& vx, float& vy);
	void RandomDirection();
};

