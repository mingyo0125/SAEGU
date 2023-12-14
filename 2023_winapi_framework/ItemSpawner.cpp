#include "pch.h"
#include "ItemSpawner.h"
#include "Core.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "Scene.h"
#include <time.h>
#include <utility>
#include "Item.h"
#include "NosItem.h"
#include "XItem.h"
#include "ResMgr.h"
#include "Texture.h"
#include "BaseWindow.h"

float scale = 20;

void SpawnItem(ItemType it, Vec2 spPos)
{
	Core::GetInst()->GetMainDC();
	switch (it)
	{
	case Nos:
	{
		
		Object* pItem = new NosItem(spPos);
		pItem->SetPos(spPos);
		pItem->SetScale(Vec2(scale, scale));

		// 1. 기본 옮기기
		SceneMgr::GetInst()->GetCurScene()->AddObject(pItem, OBJECT_GROUP::ITEM);
		break;
	}
	case X:
	{

		Object* pItem = new XItem(spPos);
		pItem->SetPos(spPos);
		pItem->SetScale(Vec2(scale, scale));
		SceneMgr::GetInst()->GetCurScene()->AddObject(pItem, OBJECT_GROUP::ITEM);
		break;
	}
	default:
		break;
	}
}

void ItemSpawner::RandomItemSpawn(Vec2 spawnPos)
{
	srand((unsigned int)time(NULL));

	ItemType it = rand() % 2 ? ItemType::Nos : ItemType::X;
	SpawnItem(it, spawnPos);
}
