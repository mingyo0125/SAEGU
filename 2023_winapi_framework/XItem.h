#pragma once
#include "Item.h"
#include "ItemEffecter.h"

class XItem : public Item
{
public:
	XItem(Vec2 spawnPos);
	~XItem();
public:
	virtual void EnterCollision(Collider* _pOther) override;
	void Render(HDC _dc) override;
	Vec2 _spawnPos;
};
