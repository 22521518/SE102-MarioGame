#include "GameObjectMovable.h"
#include "Game.h"

CGameObjectMovable::CGameObjectMovable(float x, float y, LPTEXTURE* textures)
{
	this->x = x;
	this->y = y;
	this->m_textures = textures;
	this->texture = textures[this->m_direction];
	this->m_vx = 0;
	this->m_vy = 0;
}

CGameObjectMovable::CGameObjectMovable(float x, float y, float vx, float vy, LPTEXTURE* textures)
{
	this->x = x;
	this->y = y;
	this->m_textures = textures;
	this->texture = textures[this->m_direction];
	this->m_vx = vx;
	this->m_vy = vy;
}

CGameObjectMovable::CGameObjectMovable(CGameObjectMovable* obj)
{
	this->x = obj->x;
	this->y = obj->y;
	this->m_textures = obj->m_textures;
	this->texture = obj->texture;
	this->m_vx = obj->m_vx;
	this->m_vy = obj->m_vy;
	this->m_direction = obj->m_direction;
}

void CGameObjectMovable::UpdateVelocity(float& vx, float& vy)
{
	vx = this->m_vx;
	vy = this->m_vy;
	SetDirection(this->m_direction);
}

void CGameObjectMovable::HandleBoundaryConstraints()
{
	float offsetX = this->texture->getWidth() / 2;
	float offsetY = this->texture->getHeight() / 2;
	float BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth() - offsetX;
	float BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight() - offsetY;

	if (this->GetX() <= offsetX || this->GetX() >= BackBufferWidth)
	{
		if (this->GetX() <= offsetX)
		{
			this->SetX(offsetX);
		}
		else if (this->GetX() >= BackBufferWidth)
		{
			this->SetX(BackBufferWidth);
		}
	}

	if (this->GetY() <= offsetY || this->GetY() >= BackBufferHeight)
	{
		if (this->GetY() <= offsetY)
		{
			this->SetY(offsetY);
		}
		else if (this->GetY() >= BackBufferHeight)
		{
			this->SetY(BackBufferHeight);
		}
	}
}

CGameObjectMovable::~CGameObjectMovable() {
}

void CGameObjectMovable::Update(DWORD dt)
{
	float vx = 0, vy = 0;
	this->UpdateVelocity(vx, vy);
	this->SetPosition(this->GetX() + vx * dt, this->GetY() + vy * dt);
	this->HandleBoundaryConstraints();
	
}

void CGameObjectMovable::Render()
{
	CGame::GetInstance()->Draw(this->GetX(), this->GetY(), texture);
}

bool CGameObjectMovable::IsColliding(CGameObject* object)
{
	if (!this->texture || !object->GetTexture()) return false;

	float srcMinX = this->x;
	float srcMaxX = this->x + this->texture->getWidth() / 2.0f;
	float srcMinY = this->y;
	float srcMaxY = this->y + this->texture->getHeight() / 2.0f; 

	float destMinX = object->GetX();
	float destMaxX = object->GetX() + object->GetTexture()->getWidth() / 2.0f;
	float destMinY = object->GetY();
	float destMaxY = object->GetY() + object->GetTexture()->getHeight() / 2.0f;

	return (srcMinX < destMaxX && srcMaxX > destMinX) &&
		(srcMinY < destMaxY && srcMaxY > destMinY);
}

void CGameObjectMovable::SetDirection(EDIRECTION direction)
{
	this->m_direction = direction;
	this->texture = this->m_textures[this->m_direction];
}
