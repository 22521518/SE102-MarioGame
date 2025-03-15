#include "Game.h"
#include "Mario.h"
#include "debug.h"

CMario::CMario(float x, float y, float vx):CGameObject(x, y)
{
	this->vx = vx;
};

void CMario::UpdateVecolity()
{
	current_vx = 0;
	if (GetAsyncKeyState(VK_LEFT))
	{
		current_vx = -this->vx;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		current_vx = this->vx;
	}
}

void CMario::Update(DWORD dt)
{
	UpdateVecolity();
	x += current_vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}

void CMario::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (this->current_vx >0) ani = CAnimations::GetInstance()->Get(500);
	else if (this->current_vx < 0) ani = CAnimations::GetInstance()->Get(501);
	else ani = CAnimations::GetInstance()->Get(502);

	DebugOutTitle(L"vx: %f\n", this->GetVx());
	ani->Render(x, y);
}

void CBrick::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(510);

	ani->Render(x, y);

}


CCappa::CCappa(float x, float y, float vx) :CGameObject(x, y)
{
	this->vx = vx;
};


void CCappa::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}

void CCappa::Render()
{
	LPANIMATION ani;

	if (vx > 0) ani = CAnimations::GetInstance()->Get(600);
	else ani = CAnimations::GetInstance()->Get(601);

	ani->Render(x, y);
}
