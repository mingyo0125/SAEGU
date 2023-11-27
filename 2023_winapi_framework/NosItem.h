#pragma once
#include "Item.h"

class NosItem : public Item
{
public:
	NosItem(Vec2 spawnPos);
	~NosItem();
public:
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void UseItem() override;
	Vec2 _spawnPos;
};