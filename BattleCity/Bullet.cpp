#include "Bullet.h"
#include "Game.h"

CBullet::CBullet(CBullet* obj)
{
	this->x = obj->x;
	this->y = obj->y;
	this->m_textures = obj->m_textures;
	this->texture = obj->texture;
	this->m_vx = obj->m_vx;
	this->m_vy = obj->m_vy;
	this->m_direction = obj->m_direction;
}

void CBullet::HandleBoundaryConstraints()
{
	int offsetX = this->texture->getWidth() / 2;
	int offsetY = this->texture->getHeight() / 2;
	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth() + offsetX;
	int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight() + offsetY;

	if (this->x <= -offsetX || this->x >= BackBufferWidth || this->y <= -offsetY || this->y >= BackBufferHeight)
	{
		SetActive(false);
	}
	
}

CBullet::~CBullet()
{
}

void CBullet::OnCollision()
{
	SetActive(false);
}

void CBullet::UpdateVelocity(float& vx, float& vy)
{
	switch (m_direction)
	{
	case UP:
		vy = -m_vy;
		break;
	case DOWN:
		vy = m_vy;
		break;
	case LEFT:
		vx = -m_vx;
		break;
	case RIGHT:
		vx = m_vx;
		break;
	default:
		break;
	}
}

void CBullet::Reset(float x, float y, EDIRECTION dir)
{
	SetActive(true);
	SetPosition(x, y);
	SetDirection(dir);
}