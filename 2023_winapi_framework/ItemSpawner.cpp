#include "ItemSpawner.h"
#include "pch.h"
#include "Core.h"
#include "Vec2.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "Scene.h"
#include <time.h>
#include <utility>
#include "Item.h"
#include "NosItem.h"
#include "XItem.h"

void RandomItemSpawn(Vec2 spawnPos)
{
	srand((unsigned int)time(NULL));

	ItemType it = rand() % 2 ? ItemType::Nos : ItemType::X;
	SpawnItem(it, spawnPos);
}

void SpawnItem(ItemType it, Vec2 spPos)
{
	switch (it)
	{
	case Nos: 
	{
		Item item = NosItem(spPos);
		break;
	}
	case X:
	{
		//Item item = XItem(spPos);
		break;
	}
	default:
		break;
	}
}
