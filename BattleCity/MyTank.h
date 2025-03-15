#pragma once

#include "Tank.h"

class CMyTank :
	public CTank
{
	int* done = NULL;
public:
	CMyTank() : CTank() { done = NULL; };
	CMyTank(float x, float y, float vx, float vy, LPTEXTURE* textures, int& done)
		: CTank(x, y, vx, vy, textures) {
		this->done = &done;
		if (!this->bullet) {
			this->bullet = new CBullet(x, y, 0.1f, 0.1f, CGameObjectPool::GetInstance()->GetBulletTex());
			CGameObjectPool::GetInstance()->AddBulletObject(this->bullet);
		}
	};

	virtual void OnCollision();
	virtual void UpdateVelocity(float& vx, float& vy);

	void SetDone(int done) { *(this->done) = done; };
	int GetDone() { return *done; };
};

