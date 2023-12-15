#pragma once
#include "Item.h"

class NosItem : public Item
{
public:
	NosItem(Vec2 spawnPos);
	~NosItem();
public:
	virtual void EnterCollision(Collider* _pOther) override;
	void Render(HDC _dc) override;
	Vec2 _spawnPos;
private:
	Texture* i_texture;
};