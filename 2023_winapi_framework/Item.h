#pragma once
#include "Object.h"
#include "Player.h"
#include "ItemSpawner.h"

class Item : public Object
{
public:
	Item(Vec2 spawnPos);
	~Item();
public:
	void Update() override;
	virtual void UseItem();
	Vec2 _spawnPos;
};
