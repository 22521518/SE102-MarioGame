#include "GameObjectPool.h"
#include "Game.h"
#include "TexturePath.h"
#include "EDIRECTION.h"
#include "debug.h"

void CGameObjectPool::LoadResources()
{
	myTankTex[UP] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_TANK_UP);
	myTankTex[DOWN] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_TANK_DOWN);
	myTankTex[LEFT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_TANK_LEFT);
	myTankTex[RIGHT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_TANK_RIGHT);

	greenEnemyTex[UP] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_UP);
	greenEnemyTex[DOWN] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_DOWN);
	greenEnemyTex[LEFT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_LEFT);
	greenEnemyTex[RIGHT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_GREEN_RIGHT);

	whiteEnemyTex[UP] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_UP);
	whiteEnemyTex[DOWN] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_DOWN);
	whiteEnemyTex[LEFT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_LEFT);
	whiteEnemyTex[RIGHT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_WHITE_RIGHT);

	redEnemyTex[UP] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_RED_UP);
	redEnemyTex[DOWN] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_RED_DOWN);
	redEnemyTex[LEFT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_RED_LEFT);
	redEnemyTex[RIGHT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_ENEMY_RED_RIGHT);

	bulletTex[UP] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET_UP);
	bulletTex[DOWN] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET_DOWN);
	bulletTex[LEFT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET_LEFT);
	bulletTex[RIGHT] = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET_RIGHT);
}

CGameObjectPool* CGameObjectPool::m_instance = NULL;
CGameObjectPool* CGameObjectPool::GetInstance()
{
	if (m_instance == NULL) m_instance = new CGameObjectPool();
	return m_instance;
}

CGameObjectPool::~CGameObjectPool()
{
	if (m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}

	for (int i = 0; i < m_activeObjects.size(); i++)
	{
		delete m_activeObjects[i];
	}

	for (int i = 0; i < m_bulletObjects.size(); i++)
	{
		delete m_bulletObjects[i];
	}
}

void CGameObjectPool::AddActiveObject(LPGAMEOBJECTMOVABLE object)
{
	if (!object) return;
	m_activeObjects.push_back(object);
	DebugOut(L"[INFO] Add object successfully\n");
}

void CGameObjectPool::AddBulletObject(LPBULLET object)
{
	if (!object) return;	
	m_bulletObjects.push_back(object);
	DebugOut(L"[INFO] Add bullet successfully\n");
}

int CGameObjectPool::GetActiveObjectSize()
{
	int cnt = m_activeObjects.size();
	for (int i = 0; i < m_activeObjects.size(); i++)
	{
		if (!m_activeObjects[i]->IsActive()) cnt--;
	}
	return cnt;
}

void CGameObjectPool::CheckAllObjectCollision()
{
	for (int i = 0; i < m_activeObjects.size(); i++)
	{
		if (!m_activeObjects[i]->IsActive()) continue;
		for (int j = 0; j < m_bulletObjects.size(); j++)
		{
			if (!m_bulletObjects[j]->IsActive()) continue;
			if (m_bulletObjects[j]->IsColliding(m_activeObjects[i]))
			{
				m_activeObjects[i]->OnCollision();
				m_bulletObjects[j]->OnCollision();
			}
			if (!m_activeObjects[i]->IsActive()) break;
		}
	}
}

void CGameObjectPool::Update(DWORD dt)
{

	for (int i = 0; i < m_activeObjects.size(); i++)
	{
		if (!m_activeObjects[i]->IsActive() && GetActiveObjectSize() > 3) continue;
		else if (!m_activeObjects[i]->IsActive() && GetActiveObjectSize() <= 3 && rand() % 3)
		{
			m_activeObjects[i]->Reset();
		}
		m_activeObjects[i]->Update(dt);
	}
	for (int i = 0; i < m_bulletObjects.size(); i++)
	{
		if (!m_bulletObjects[i]->IsActive()) continue;
		m_bulletObjects[i]->Update(dt);
	}
}

void CGameObjectPool::Render()
{
	for (int i = 0; i < m_activeObjects.size(); i++)
	{
		if (!m_activeObjects[i]->IsActive()) continue;
		m_activeObjects[i]->Render();
	}
	for (int i = 0; i < m_bulletObjects.size(); i++)
	{
		if (!m_bulletObjects[i]->IsActive()) continue;
		m_bulletObjects[i]->Render();
	}
}

