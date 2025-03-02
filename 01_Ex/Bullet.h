#pragma once
#include "GameObject.h"
class CBullet :
    public CGameObject
{
    float vy;
public:
	CBullet(float x, float y, float vy, LPTEXTURE texture) : CGameObject(x, y, texture)
	{
		this->vy = vy;
	};
	void Update(DWORD dt) 
	{
		y += vy * dt;
	};
};

