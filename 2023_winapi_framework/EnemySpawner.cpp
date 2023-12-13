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
#include "Timer.h"
#include <time.h>
#include <utility>

EnemySpawner::EnemySpawner(Object* targetObj, float speed, int hp, float scale, Timer* timer)
{
	p_target = targetObj;
	fMonsterSpeed = speed;
	fMonsterHp = hp;
	fMonsterScale = scale;
	p_timer = timer;
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
		pMonster = new BatMonster(p_target, fMonsterSpeed, fMonsterHp);
		break;
	}
	case 1:
	{
		pMonster = new BirdMonster(p_target, fMonsterSpeed, fMonsterHp);
		break;
	}
	case 2:
	{
		pMonster = new SlimeMonster(p_target, fMonsterSpeed, fMonsterHp);
	}
	default:
		break;
	}

	pMonster->SetPos(GetSpawnPos());
	pMonster->SetScale(Vec2(fMonsterScale, fMonsterScale));
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

void EnemySpawner::Update()
{
	if (fCurrentTime >= GetSpawnTime(p_timer->t_currentSecnod))
	{
		SpawnEnemy();
		fCurrentTime = 0;
	}
	fCurrentTime += fDT;
}

float EnemySpawner::GetSpawnTime(int second)
{


	return 0.0f;
}
