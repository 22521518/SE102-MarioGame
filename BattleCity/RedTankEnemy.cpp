#include "RedTankEnemy.h"
#include "GreenTankEnemy.h"

void CRedTankEnemy::OnCollision()
{
	this->SetActive(false);
	DebugOut(L"Red Tank Enemy is destroyed\n");

	CGreenTankEnemy* greenTank = new CGreenTankEnemy(this->GetX(), this->GetY(), this->GetVx(), this->GetVy(), CGameObjectPool::GetInstance()->GetGreenEnemyTex());
	greenTank->SetActive(true);
	greenTank->SetDirection(this->m_direction);
	CGameObjectPool::GetInstance()->AddActiveObject(greenTank);
}
