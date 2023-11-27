#include "pch.h"
#include "NosItem.h"

NosItem::NosItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	_spawnPos = spawnPos;

}
NosItem::~NosItem()
{

}

void NosItem::EnterCollision(Collider* _pOther)
{
	UseItem();
}

void NosItem::UseItem()
{
}
