#include "WhiteTankEnemy.h"

void CWhiteTankEnemy::OnCollision()
{
	DebugOut(L"White Tank Enemy is destroyed\n");
	this->SetActive(false);
}