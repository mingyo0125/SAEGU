#include "pch.h"
#include "XItem.h"

XItem::XItem(Vec2 spawnPos)
	:Item(spawnPos)
{
	_spawnPos = spawnPos;

}
XItem::~XItem()
{

}

void XItem::EnterCollision(Collider* _pOther)
{
	UseItem();
}

void XItem::UseItem()
{
}