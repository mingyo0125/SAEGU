#pragma once
#include "Item.h"

class XItem : public Item
{
public:
	XItem(Vec2 spawnPos);
	~XItem();
public:
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void UseItem() override;
	void Render(HDC _dc) override;
	Vec2 _spawnPos;
};
