#include "TankEnemy.h"

void CTankEnemy::UpdateVelocity(float& vx, float& vy)
{
	RandomDirection();
	switch (this->GetDirection())
	{
	case UP:
		vy = -this->GetVy();
		vx = 0;
		break;
	case DOWN:
		vy = this->GetVy();
		vx = 0;
		break;
	case LEFT:
		vx = -this->GetVx();
		vy = 0;
		break;
	case RIGHT:
		vx = this->GetVx();
		vy = 0;
		break;
	default:
		break;
	}
    Fire();
}

void CTankEnemy::RandomDirection()
{

	if (this->GetDirection() == UP && this->GetY() < this->texture->getHeight())
	{
		this->SetDirection(DOWN);
		return;
	}
	else if (this->GetDirection() == DOWN && this->GetY() > CGame::GetInstance()->GetBackBufferHeight() - this->texture->getHeight())
	{
		this->SetDirection(UP);
		return;
	}
	else if (this->GetDirection() == LEFT && this->GetX() < this->texture->getWidth())
	{
		this->SetDirection(RIGHT);
		return;
	}
	else if (this->GetDirection() == RIGHT && this->GetX() > CGame::GetInstance()->GetBackBufferWidth() - this->texture->getWidth())
	{
		this->SetDirection(LEFT);
		return;
	}
	

	if (--m_timeToChangeDirection <= 0)
	{
		int newDirection = rand() % 4;

		switch (newDirection)
		{
		case 0: this->SetDirection(LEFT); break;
		case 1: this->SetDirection(RIGHT); break;
		case 2: this->SetDirection(UP); break;
		case 3: this->SetDirection(DOWN); break;
		default:
			break;
		}
		m_timeToChangeDirection = rand() % 100;
		if (m_timeToChangeDirection < 25) m_timeToChangeDirection = 25;

	}
}


