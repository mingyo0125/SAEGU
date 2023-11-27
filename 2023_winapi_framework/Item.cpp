#include "pch.h"
#include "Item.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Object.h"
#include "EventMgr.h"

Item::Item(Vec2 spawnPos)
	:_spawnPos(spawnPos)
{
	_spawnPos = spawnPos;
}

Item::~Item()
{
}

void Item::Update()
{
}

void Item::UseItem()
{
}


