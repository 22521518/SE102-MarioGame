#pragma once
#include<vector>
#include "Sprite.h"

using namespace std;

/*
	Sprite animation
*/
class CAnimationFrame
{
	vector<LPSPRITE> sprites;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) {
		sprites.push_back(sprite);
		this->time = time;
	}

	CAnimationFrame(vector<LPSPRITE> sprite, int time) {
		for (int i = 0; i < sprite.size(); i++) 
			sprites.push_back(sprite[i]);
		this->time = time;
	}

	DWORD GetTime() { return time; }
	vector<LPSPRITE> GetSprites() { return sprites; }
	virtual void Draw(float x, float y);
};

typedef CAnimationFrame* LPANIMATION_FRAME;

