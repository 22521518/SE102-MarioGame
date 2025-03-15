#pragma once
#include "GameObject.h"

class CGameObjectCollidable : public CGameObject
{
public:
    CGameObjectCollidable()
        : CGameObject() {
    };
    CGameObjectCollidable(float x, float y, LPTEXTURE texture)
        : CGameObject(x, y, texture) {
    };
    CGameObjectCollidable(CGameObject* obj)
        : CGameObject(obj) {
    };
    virtual bool IsColliding(CGameObject* object) = 0;
    virtual void OnCollision() = 0;
};

typedef CGameObjectCollidable* LPGAMEOBJECTCOLLIDABLE;