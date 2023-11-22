#include "pch.h"
#include "Core.h"
#include "Vec2.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "EnemySpawner.h"
#include "Scene.h"

void SpawnEnemy(Object* targetObj, float speed, int hp, float scale)
{
	Monster* pMonster = new Monster(targetObj, speed, hp);
	pMonster->SetPos(Vec2(100, 100));
	pMonster->SetScale(Vec2(scale, scale));
	pMonster->SetCenterPos(pMonster->GetPos());

	SceneMgr::GetInst()->GetCurScene()->AddObject(pMonster, OBJECT_GROUP::BULLET);
}
