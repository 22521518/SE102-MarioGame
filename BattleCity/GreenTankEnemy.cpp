#include "GreenTankEnemy.h"
#include "WhiteTankEnemy.h"
#include "GameObjectPool.h"

void CGreenTankEnemy::OnCollision()
{
	DebugOut(L"Green Tank Enemy is destroyed\n");
	this->SetActive(false);
	CWhiteTankEnemy* whiteTank = new CWhiteTankEnemy(this->GetX(), this->GetY(), this->GetVx(), this->GetVy(), CGameObjectPool::GetInstance()->GetWhiteEnemyTex());
	whiteTank->SetActive(true);
	whiteTank->SetDirection(this->m_direction);
	CGameObjectPool::GetInstance()->AddActiveObject(whiteTank);
}
