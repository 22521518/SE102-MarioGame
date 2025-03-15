#pragma once
#include "GameObjectMovable.h"

class CTankBullet : public CGameObjectMovable {
public:
	CTankBullet(float x, float y, float vx, float vy, LPTEXTURE texture) : CGameObjectMovable(x, y, vx, vy, texture) {};
	~CTankBullet() {
		if (texture != NULL) delete texture;
	};

	void checkMove(float& v_x, float& v_y) override {
		v_x = vx;
		v_y = vy;
	}
};