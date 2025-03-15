#include "GameObject.h"
#include "Game.h"

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}

void CGameObject::Reset()
{
	int x = rand() % (CGame::GetInstance()->GetBackBufferWidth() - this->GetTexture()->getWidth());
	this->SetActive(true);
	this->SetPosition(x, 0);

}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}