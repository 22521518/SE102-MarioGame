#pragma once

#include "GameObject.h"
#include "Game.h"

class CGameObjectMovable : public CGameObject {
protected:
	float vx;
	float vy;
public:
	virtual void checkMove(float& v_x, float& v_y) = 0;

	CGameObjectMovable() : CGameObject() {
		this->vx = 0;
		this->vy = 0;
	}

	CGameObjectMovable(float x, float y, LPTEXTURE texture) : CGameObject(x, y, texture)
	{
		this->vx = 0;
		this->vy = 0;
	}

	CGameObjectMovable(float x, float y, float vx, float vy, LPTEXTURE texture) : CGameObject(x, y, texture)
	{
		this->vx = vx;
		this->vy = vy;
	}

	~CGameObjectMovable() {
		if (texture != NULL) delete texture;
	}

	void Update(DWORD dt) {
		float v_x = 0, v_y = 0;
		checkMove(v_x, v_y);
		x += v_x * dt;
		y += v_y * dt;

		int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - texture->getWidth())
		{
			x = (float)(BackBufferWidth - texture->getWidth());
		}
		if (y <= 0)
		{
			y = 0;
		}
		else if (y >= CGame::GetInstance()->GetBackBufferHeight() - texture->getHeight())
		{
			y = (float)(CGame::GetInstance()->GetBackBufferHeight() - texture->getHeight());
		}
	}

	void Render() {
		CGameObject::Render();
	}
};