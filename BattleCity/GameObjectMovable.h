#pragma once

#include "GameObjectCollidable.h"
#include "EDIRECTION.h"

class CGameObjectMovable : public CGameObjectCollidable
{
protected:
	LPTEXTURE* m_textures = NULL;
	EDIRECTION m_direction = UP;
	float m_vx = 0, m_vy = 0;
public:
	CGameObjectMovable(): CGameObjectCollidable() {};
	CGameObjectMovable(float x, float y, LPTEXTURE* texture);
	CGameObjectMovable(float x, float y, float vx, float vy, LPTEXTURE* textures);
	CGameObjectMovable(CGameObjectMovable* obj);
	~CGameObjectMovable();

	virtual void UpdateVelocity(float& vx, float& vy);
	virtual void HandleBoundaryConstraints();

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual bool IsColliding(CGameObject* object);
	virtual void OnCollision() = 0;

	EDIRECTION GetDirection() { return m_direction; };
	void SetVx(float vx) { this->m_vx = vx; };
	void SetVy(float vy) { this->m_vy = vy; };
	float GetVx() const { return m_vx; };
	float GetVy() const { return m_vy; };
	void SetDirection(EDIRECTION direction);
};

typedef CGameObjectMovable* LPGAMEOBJECTMOVABLE;