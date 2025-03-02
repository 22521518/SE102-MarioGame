#pragma once
#include "GameObject.h"
#include <random>

class CShip :
    public CGameObject
{
	float vx, vy;
	// Function to generate a random float between min and max
	float getRandomFloat(float min, float max) {
		static std::random_device rd;  // Random seed
		static std::mt19937 gen(rd()); // Mersenne Twister engine
		std::uniform_real_distribution<float> dist(min, max); // Range

		return dist(gen);
	}
public:
	CShip(float x, float y, float vx, float vy, LPTEXTURE texture) : CGameObject(x, y, texture) 
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);
};

