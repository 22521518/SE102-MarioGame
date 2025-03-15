#include "Tank.h"
#include "GameObjectPool.h"

CTank::CTank() : CGameObjectMovable()
{
	bullet = new CBullet(x, y, this->GetBulletSpeed(), this->GetBulletSpeed(), CGameObjectPool::GetInstance()->GetBulletTex());
	bullet->SetActive(false);
	CGameObjectPool::GetInstance()->AddBulletObject(bullet);
}

CTank::CTank(float x, float y, float vx, float vy, LPTEXTURE* textures) :
	CGameObjectMovable(x, y, vx, vy, textures)
{
	bullet = new CBullet(x, y, this->GetBulletSpeed(), this->GetBulletSpeed(), CGameObjectPool::GetInstance()->GetBulletTex());
	bullet->SetActive(false);
	CGameObjectPool::GetInstance()->AddBulletObject(bullet);
}

CTank::CTank(CTank* obj)
{
	this->x = obj->x;
	this->y = obj->y;
	this->m_textures = obj->m_textures;
	this->texture = obj->texture;
	this->m_vx = obj->m_vx;
	this->m_vy = obj->m_vy;
	this->m_direction = obj->m_direction;
	this->bullet = obj->bullet->clone();
	this->bullet->SetActive(false);
	CGameObjectPool::GetInstance()->AddBulletObject(this->bullet);
};

void CTank::Fire() 
{
	if (!bullet) return;
	if (bullet->IsActive()) return;

	int offsetX = this->texture->getWidth() / 2;
	int offsetY = this->texture->getHeight() / 2;

	if (m_direction == UP)
	{
		offsetX = 0;
		offsetY = -offsetY;
	}
	else if (m_direction == DOWN)
	{
		offsetX = 0;
		offsetY = offsetY;
	}
	else if (m_direction == LEFT)
	{
		offsetX = -offsetX;
		offsetY = 0;
	}
	else if (m_direction == RIGHT)
	{
		offsetX = offsetX;
		offsetY = 0;
	}
	bullet->Reset(this->x + offsetX, this->y + offsetY, m_direction);
}