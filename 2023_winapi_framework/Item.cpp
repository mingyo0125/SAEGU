#include "pch.h"
#include "Item.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Object.h"
#include "EventMgr.h"

float _moveSpeed = 0.02f;
float _moveDistance = 1;

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
	float value = sin(fDT * _moveSpeed) * _moveDistance;
	SetPos(Vec2(_spawnPos.x, _spawnPos.y + value));

}

void Item::UseItem()
{
}


