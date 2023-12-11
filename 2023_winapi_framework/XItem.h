#pragma once
#include "Item.h"

class XItem : public Item
{
public:
	XItem(Vec2 spawnPos);
	~XItem();
public:
	void Update() override;
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void UseItem(Player* p) override;
	void Render(HDC _dc) override;
	Vec2 _spawnPos;
};
