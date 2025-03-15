#include "MyTank.h"

void CMyTank::OnCollision()
{
	this->SetActive(false); // deactivate
	this->SetDone(1); // end game
}

void CMyTank::UpdateVelocity(float& vx, float& vy)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vx = -this->GetVx();
		this->SetDirection(LEFT);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) 
	{
		vx = this->GetVx();
		this->SetDirection(RIGHT);
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		vy = -this->GetVy();
		this->SetDirection(UP);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		vy = this->GetVy();
		this->SetDirection(DOWN);
	}
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Fire();
	}
}
