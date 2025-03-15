#pragma once
#include <vector>
#include "GameObjectMovable.h"
#include "Bullet.h"

using namespace std;

class CGameObjectPool
{
	static CGameObjectPool* m_instance;
	CGameObjectPool() {};

	LPTEXTURE* myTankTex = new LPTEXTURE[4];
	LPTEXTURE* greenEnemyTex = new LPTEXTURE[4];
	LPTEXTURE* whiteEnemyTex = new LPTEXTURE[4];
	LPTEXTURE* redEnemyTex = new LPTEXTURE[4];
	LPTEXTURE* bulletTex = new LPTEXTURE[4];
	
	vector<LPGAMEOBJECTMOVABLE> m_activeObjects;
	vector<LPBULLET> m_bulletObjects;

public:
	static CGameObjectPool* GetInstance();
	~CGameObjectPool();

	void LoadResources();

	void AddActiveObject(LPGAMEOBJECTMOVABLE object);
	void AddBulletObject(LPBULLET object);

	int GetActiveObjectSize();
	void CheckAllObjectCollision();

	void Update(DWORD dt);
	void Render();

	LPTEXTURE* GetMyTankTex() { return myTankTex; }
	LPTEXTURE* GetGreenEnemyTex() { return greenEnemyTex; }
	LPTEXTURE* GetWhiteEnemyTex() { return whiteEnemyTex; }
	LPTEXTURE* GetRedEnemyTex() { return redEnemyTex; }
	LPTEXTURE* GetBulletTex() { return bulletTex; }
};

