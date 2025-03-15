#pragma once
#include <Windows.h>
#include "Texture.h"

class CGameObject
{
protected:
	float x = 0;
	float y = 0;
	bool active = true;
	LPTEXTURE texture = NULL;
public:
	CGameObject(float x = 0.0f, float y = 0.0f, LPTEXTURE texture = NULL)
		: x(x), y(y), texture(texture), active(true) {
	}

	CGameObject(CGameObject* obj)
		: x(obj->x), y(obj->y), active(obj->active), texture(obj->texture) {
	}

	virtual void Update(DWORD dt) = 0;
	virtual void Render();
	virtual void Reset();
	~CGameObject();

	LPTEXTURE GetTexture() { return texture; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	bool IsActive() { return this->active; }
	void SetActive(bool active) { this->active = active; }
};

typedef CGameObject* LPGAMEOBJECT;