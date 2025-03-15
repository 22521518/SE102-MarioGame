#include "AnimationFrame.h"

void CAnimationFrame::Draw(float x, float y)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		LPTEXTURE tex = sprites[i]->GetTexture();
		int h = tex->getHeight() + 2;
		sprites[i]->Draw(x, y + h * i);
	}
}
