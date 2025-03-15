#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define MARIO_WIDTH 14

class CBrick : public CGameObject {
public: 
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CMario : public CGameObject
{
protected:
	float vx;
	float current_vx;
public:
	CMario(float x, float y, float vx);
	float GetVx() { return vx; }	
	void UpdateVecolity();
	void Update(DWORD dt);
	void Render();
};


class CCappa : public CGameObject
{
protected:
	float vx;
public:
	CCappa(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};

