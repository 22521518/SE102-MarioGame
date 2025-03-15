#pragma once
#include "GameObjectMovable.h"
class CBullet :
    public CGameObjectMovable
{
protected:
	bool active = false;

public:
	CBullet(float x, float y, float vx, float vy, LPTEXTURE* textures) :
		CGameObjectMovable(x, y, vx, vy, textures) {};
	CBullet(CBullet* obj);
	~CBullet();

	virtual void HandleBoundaryConstraints();
	virtual void OnCollision();
	virtual void UpdateVelocity(float& vx, float& vy);
	virtual void Reset(float x, float y, EDIRECTION dir);
	virtual CBullet* clone() { return new CBullet(*this); };
};

typedef CBullet* LPBULLET;