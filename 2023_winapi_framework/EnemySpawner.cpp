#include "pch.h"
#include "Core.h"
#include "Vec2.h"
#include "Monster.h"
#include "BatMonster.h"
#include "BirdMonster.h"
#include "SlimeMonster.h"
#include "SceneMgr.h"
#include "EnemySpawner.h"
#include "Scene.h"
#include "ItemSpawner.h"
#include <time.h>
#include <utility>

void EnemySpawner::SpawnEnemy(Object* targetObj, float speed, int hp, float scale)
{
	srand((unsigned int)time(NULL));
	int randomMonster = rand() % 3;
	
	Monster* pMonster = nullptr;
	switch (randomMonster)
	{
	case 0:
	{
		pMonster = new BatMonster(targetObj, speed, hp);
		break;
	}
	case 1:
	{
		pMonster = new BirdMonster(targetObj, speed, hp);
		break;
	}
	case 2:
	{
		pMonster = new SlimeMonster(targetObj, speed, hp);
	}
	default:
		break;
	}

	pMonster->SetPos(GetSpawnPos());
	pMonster->SetScale(Vec2(scale, scale));
	pMonster->SetCenterPos(pMonster->GetPos());

	SceneMgr::GetInst()->GetCurScene()->AddObject(pMonster, OBJECT_GROUP::BULLET);
}

Vec2 EnemySpawner::GetSpawnPos()
{
	srand((unsigned int)time(NULL));
	int chooseAreaIdx = rand() % 4;
	std::pair<Vec2, Vec2> chooseAreaPair = areaSizeArr[chooseAreaIdx];

	int firstElement = rand() % (int)(chooseAreaPair.second.x - chooseAreaPair.first.x) + chooseAreaPair.first.x;
	int secondElement = rand() % (int)(chooseAreaPair.second.y - chooseAreaPair.first.y) + chooseAreaPair.first.y;

	return Vec2(firstElement, secondElement);
}
