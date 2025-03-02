#pragma once
#include <d3dx10.h>
class CSprite
{
protected:
	ID3DX10Sprite* _spriteObject;
	ID3D10Device* _pD3DDevice;

	ID3D10Texture2D* _pTexture;
	D3DX10_SPRITE _pSprite;

	LPCWSTR _texturePath;

	float _x;
	float _vx;
	float _vy;
	float _y;
	float _width;
	float _height;

public:
	CSprite(
		ID3D10Device* pD3DDevice,
		ID3DX10Sprite* spriteObject,
		float x,
		float y,
		float vx,
		float vy,
		float width,
		float height,
		LPCWSTR texturePath
	);
	~CSprite();

	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, int backBufferWidth, int backBufferHeight);
	float GetX() { return _x; }
	float GetY() { return _y; }

};

