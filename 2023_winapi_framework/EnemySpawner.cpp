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
#include "TimeMgr.h"
#include <array>
#include <time.h>
#include <utility>

EnemySpawner::EnemySpawner(Object* targetObj, float speed, int hp[], float scale, Timer* timer)
{
	Object::SetName(L"EnemySpawner");

	p_target = targetObj;
	fMonsterSpeed = speed;
	fSlimeHp = 1;
	fBatHp = 2;
	fBirdHp = 3;
	fMonsterScale = scale;
	p_timer = timer;

	p_timer->t_currentSecond.HandleSecChange = &EnemySpawner::HandleSecondChange;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::SpawnEnemy()
{
	srand((unsigned int)time(NULL));
	int randomMonster = rand() % 3;
	
	Monster* pMonster = nullptr;
	switch (randomMonster)
	{
	case 0:
	{
		pMonster = new BatMonster(p_target, fMonsterSpeed, fBatHp);
		break;
	}
	case 1:
	{
		pMonster = new BirdMonster(p_target, fMonsterSpeed, fBirdHp);
		break;
	}
	case 2:
	{
		pMonster = new SlimeMonster(p_target, fMonsterSpeed, fSlimeHp);
	}
	default:
		break;
	}

	pMonster->SetPos(GetSpawnPos());
	pMonster->SetScale(Vec2(fMonsterScale, fMonsterScale));
	pMonster->SetCenterPos(pMonster->GetPos());

	SceneMgr::GetInst()->GetCurScene()->AddObject(pMonster, OBJECT_GROUP::MONSTER);
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

void EnemySpawner::Update()
{
	if (fCurrentTime >= fSpawnTime)
	{
		SpawnEnemy();
		fCurrentTime = 0;
	}
	fCurrentTime += fDT;
}

void EnemySpawner::HandleSecondChange()
{
	if (p_timer->t_currentSecond.second > limitTimeArr[idx])
	{
		idx++;
		fSpawnTime = spawnTimeArr[idx];
	}
}

