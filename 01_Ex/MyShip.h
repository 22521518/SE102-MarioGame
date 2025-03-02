#pragma once
#include "GameObject.h"
#include "Bullet.h"

#include <iostream>
#include <vector>

using namespace std;

class CMyShip :
    public CGameObject
{
	float vx, vy;
	void Input(float &v_x, float &v_y);
	vector<CBullet*> bullets;

	void RemoveBullet();

public:
	CMyShip(float x, float y, float vx, float vy, LPTEXTURE texture) : CGameObject(x, y, texture)
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);
	void Fire();
	void Render() 
	{ 
		CGameObject::Render(); 
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Render();
		}
	}
};

