#include "CSprite.h"
#include "debug.h"

CSprite::CSprite(
	ID3D10Device* pD3DDevice,
	ID3DX10Sprite* _spriteObject,
	float x,
	float y,
	float vx,
	float vy,
	float width,
	float height,
	LPCWSTR texturePath
)
{
	this->_x = x;
	this->_y = y;
	this->_vx = vx;
	this-> _vy = vy;
	this->_width = width;
	this->_height = height;
	this->_spriteObject = _spriteObject;
	this->_pD3DDevice = pD3DDevice;
	this->_texturePath = texturePath;

	this->_pTexture = NULL;
	this->_pSprite = D3DX10_SPRITE();
}

CSprite::~CSprite()
{
	if (_pTexture)
	{
		_pTexture->Release();
	}
}

void CSprite::LoadResource()
{
	ID3D10Resource* pD3D10Resource = NULL;

	// Loads the texture into a temporary ID3D10Resource object
	HRESULT hr = D3DX10CreateTextureFromFile(_pD3DDevice,
		_texturePath,
		NULL,
		NULL,
		&pD3D10Resource,
		NULL);

	// Make sure the texture was loaded successfully
	if (FAILED(hr))
	{
		DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s \n", _texturePath);
		return;
	}

	// Translates the ID3D10Resource object into a ID3D10Texture2D object
	pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&_pTexture);
	pD3D10Resource->Release();

	if (!_pTexture) {
		DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
		return;
	}

	// Get the texture details
	D3D10_TEXTURE2D_DESC desc;
	_pTexture->GetDesc(&desc);

	// Create a shader resource view of the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

	// Clear out the shader resource view description structure
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));

	// Set the texture format
	SRVDesc.Format = desc.Format;
	// Set the type of resource
	SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;

	ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

	_pD3DDevice->CreateShaderResourceView(_pTexture, &SRVDesc, &gSpriteTextureRV);

	// Set the sprite’s shader resource view
	_pSprite.pTexture = gSpriteTextureRV;

	// top-left location in U,V coords
	_pSprite.TexCoord.x = 0;
	_pSprite.TexCoord.y = 0;

	// Determine the texture size in U,V coords
	_pSprite.TexSize.x = 1.0f;
	_pSprite.TexSize.y = 1.0f;

	// Set the texture index. Single textures will use 0
	_pSprite.TextureIndex = 0;

	// The color to apply to this sprite, full color applies white.
	_pSprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	DebugOut((wchar_t*)L"[INFO] Texture loaded Ok: %s \n", _pTexture);
}

void CSprite::Render()
{
	// The translation matrix to be created
	D3DXMATRIX matTranslation;
	// Create the translation matrix
	D3DXMatrixTranslation(&matTranslation, _x, _y, 0.1f);
	// Scale the sprite to its correct width and height
	D3DXMATRIX matScaling;
	D3DXMatrixScaling(&matScaling, _width, _height, 1.0f);
	// Setting the sprite’s position and size
	_pSprite.matWorld = (matScaling * matTranslation);
	_spriteObject->DrawSpritesImmediate(&_pSprite, 1, 0, 0);
}

void CSprite::Update(DWORD dt, int backBufferWidth, int backBufferHeight)
{
	return;
}

