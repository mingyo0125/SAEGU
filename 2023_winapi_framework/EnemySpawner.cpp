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
#include "ResMgr.h"
#include "SelectGDI.h"
#include <array>
#include <time.h>
#include <utility>

EnemySpawner::EnemySpawner(Object* targetObj, float speed, int hp[], float scale, Timer* timer)
{
	Object::SetName(L"EnemySpawner");
	ResMgr::GetInst()->AddFont(L"neodgm");

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

void EnemySpawner::SpawnRandomEnemy()
{
	Monster* pMonster = nullptr;
	switch (randomT % 3)
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
	randomT++;
	if (randomT >= 200)
	{
		randomT = 0;
	}
}

Vec2 EnemySpawner::GetSpawnPos()
{
	std::pair<Vec2, Vec2> chooseAreaPair = areaSizeArr[randomS % 4];

	int firstElement = rand() % (int)(chooseAreaPair.second.x - chooseAreaPair.first.x) + chooseAreaPair.first.x;
	int secondElement = rand() % (int)(chooseAreaPair.second.y - chooseAreaPair.first.y) + chooseAreaPair.first.y;
	randomS++;
	if (randomS >= 200)
	{
		randomS = 0;
	}
	return Vec2(firstElement, secondElement);
}

void EnemySpawner::Update()
{
	if (fCrazyTime >= crazyEnemyTime)
	{
		Camera::GetInst()->CameraShake(7.f);
		fSpawnTime = 0.1f;
		onWarnning = true;
		fCrazyTime = 0;
	}

	if (onWarnning && fCrazyTime >= warnningTextTime)
	{
		onWarnning = false;
	}

	if (fCurrentTime >= fSpawnTime)
	{
		SpawnRandomEnemy();
		fCurrentTime = 0;
	}
	
	fCrazyTime += fDT;
	fCurrentTime += fDT;
}

void EnemySpawner::Render(HDC _dc)
{
	if (!onWarnning) return;

	HFONT myFont = ResMgr::GetInst()->LoadFont(L"neodgm", 50);
	SelectGDI gdi(_dc, myFont);

	SetBkMode(_dc, TRANSPARENT);
	SetTextAlign(_dc, TA_CENTER);
	SetTextColor(_dc, RGB(255, 255, 255));

	TextOut(_dc, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200,
		TEXT("적들이 몰려옵니다!!!"), 12);
}

void EnemySpawner::HandleSecondChange()
{
	if (p_timer->t_currentSecond.second > limitTimeArr[idx])
	{
		idx++;
		if(!onWarnning)
			fSpawnTime = spawnTimeArr[idx];
	}
}

