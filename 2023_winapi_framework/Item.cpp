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
	CreateCollider();
	GetCollider()->SetScale(Vec2(10, 10));
}

Item::~Item()
{
}

void Item::Update()
{
	
}

void Item::UseItem(Object* p)
{
}


