#pragma once
#include "GameObjectMovable.h"
#include "TankBullet.h"

enum DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#define BULLET_TEXTURE_PATH_LEFT L"bullet/left.png"
#define BULLET_TEXTURE_PATH_RIGHT L"bullet/right.png"
#define BULLET_TEXTURE_PATH_UP L"bullet/up.png"
#define BULLET_TEXTURE_PATH_DOWN L"bullet/down.png"

class CTank : public CGameObjectMovable {

protected:
	DIR dir;
	LPTEXTURE textureList[4];
	LPTEXTURE bulletTextureList[4];

	CTankBullet* bullet;

public:
	CTank() : CGameObjectMovable() 
	{
		bullet = NULL;
	};
    CTank(float x, float y, float vx, float vy, LPTEXTURE textures[]);

	~CTank() {
		if (texture != NULL) delete texture;
		
	};
	void checkMove(float& v_x, float& v_y);
	void Update(DWORD dt);
	void Fire();
	void Render();
};